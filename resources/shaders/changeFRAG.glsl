#version 330 core		

	
layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;

in change_TBN{
    vec3 FragPos;
    vec2 UVCoord;
    vec3 Normal;
    vec4 FragPosLightSpace;
	vec3 cameraPos;
	vec3 lightDirection;
	vec3 T;
	vec3 B;
}fs_in;
//in vec3 Normal;
//in vec3 FragPos;
//in vec2 UVCoord;

struct Material
{
 vec3 ambient;
 sampler2D diffuse;
 sampler2D specular;
 sampler2D normal;
 sampler2D emission;
 sampler2D reflection;
 float shininess;
};

struct DirectionalLight
{

	 vec3 color;
	 vec3 pos;
	 float intensity;
};




uniform sampler2D ourTexture;//自定义的全局sampler2D 变量中的值，其实是[0,15]这15个整数数字
uniform sampler2D ourFace;
uniform vec3 objColor;//objColor == albedo
uniform vec3 ambientColor;
uniform samplerCube skybox;
uniform sampler2D shadowMap;
//height map

uniform sampler2D heightMap;
uniform float height_scale;
uniform bool heightMapFlag;
uniform Material material;
uniform DirectionalLight lightD;


//计算阴影
float ShadowCalculation(vec4 fragPosLightSpace)
{
	//执行透视除法
	vec3 projCoords = fragPosLightSpace.xyz/fragPosLightSpace.w;
	// 变换到[0,1]的范围
    projCoords = projCoords * 0.5 + 0.5;
	// 取得最近点的深度(使用[0,1]范围下的fragPosLight当坐标)
    float closestDepth = texture(shadowMap, projCoords.xy).r;
	//在灯光视角下，每个片元的Z值就是当前片元在灯光视角下的深度
    float currentDepth = projCoords.z;
    float shadow =0.0;
	vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
	 for(int x = -1; x <= 1; ++x)
    {
        for(int y = -1; y <= 1; ++y)
        {
            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r; 
            shadow += currentDepth - 0.001 > pcfDepth  ? 1.0 : 0.0;        
        }    
    }
    shadow /= 9.0;
//shadow = currentDepth -0.001f> closestDepth  ? 1.0 : 0.0;
	    if(projCoords.z > 1.0)
        shadow = 0.0;
    return shadow;
}
//ParallaxMapping
vec2 ParallaxMapping(vec2 texCoords,vec3 viewDir)
{
	float height = texture(heightMap,texCoords).r;
	vec2 p = viewDir.xy / viewDir.z * (height * height_scale);
	return texCoords - p;

}




//平行光函数
vec3 CalcLightDirectional(DirectionalLight light, vec3 unitNormal,vec3 viewDir)
{
	//diffuse max(0,dot(n,l)) 
	float diffuseIntensity = max(0,dot(unitNormal,fs_in.lightDirection));
	vec3 diffuseColor = diffuseIntensity * light.color * texture(material.diffuse,fs_in.UVCoord).rgb;
	//specular dot(R,V)
	vec3 refDir = reflect(-fs_in.lightDirection,unitNormal);
	float specularIntensity = pow(max(0,dot(refDir,viewDir)),material.shininess);
	vec3 specularColor = specularIntensity * light.color ;
	//ref
	vec3 refMask = texture(material.reflection,fs_in.UVCoord).xyz;
	vec3 ViewDirToFrag = normalize(fs_in.FragPos - fs_in.cameraPos);
	vec3 R = reflect(ViewDirToFrag,unitNormal);
	vec3 refColor = texture(skybox,R).xyz * refMask * light.color ;
	//ambient
	vec3 ambient =  material.ambient*texture(material.diffuse,fs_in.UVCoord).rgb* light.color;
	float shadow = ShadowCalculation(fs_in.FragPosLightSpace);
	//TODO 反射不能够和漫反射共存，不知道原因
	vec3 result = ((diffuseColor+specularColor)*(1-shadow)+ambient)* light.intensity;
//	vec3 result = diffuseColor ;
	return result;
}
//视差
vec3 CalcLightDirectional(DirectionalLight light,vec3 tangentLightDir,vec3 unitNormal,vec3 viewDir,vec2 texCoords)
{
	//diffuse max(0,dot(n,l)) 
	float diffuseIntensity = max(0,dot(unitNormal,tangentLightDir));
	vec3 diffuseColor = diffuseIntensity * light.color * texture(material.diffuse,texCoords).rgb;
	//specular dot(R,V)
	vec3 refDir = reflect(tangentLightDir,unitNormal);
	float specularIntensity = pow(max(0,dot(refDir,viewDir)),material.shininess);
	vec3 specularColor = specularIntensity * light.color ;
	//ref
	vec3 refMask = texture(material.reflection,texCoords).xyz;
	vec3 ViewDirToFrag = normalize(fs_in.FragPos - fs_in.cameraPos);
	vec3 R = reflect(ViewDirToFrag,unitNormal);
	vec3 refColor = texture(skybox,R).xyz * refMask * light.color ;
	//ambient
	vec3 ambient =  material.ambient*texture(material.diffuse,texCoords).rgb* light.color;
	float shadow = ShadowCalculation(fs_in.FragPosLightSpace);
	//TODO 反射不能够和漫反射共存，不知道原因
	vec3 result = ((diffuseColor+specularColor)*(1-shadow)+ambient)* light.intensity;
//	vec3 result = diffuseColor ;
	return result;
}



void main()
{
//	vec4 refMask = texture(material.reflection,UVCoord);
//	vec3 ViewDirToFrag = normalize(FragPos - cameraPos);
//	vec3 R = reflect(ViewDirToFrag, normalize(Normal));
	//TBN
	vec3 T = normalize(fs_in.T);
	vec3 B = normalize(fs_in.B);
	vec3 N = normalize(fs_in.Normal);
	mat3 TBN = mat3(T,B,N);


	vec3 viewDir = normalize(fs_in.cameraPos - fs_in.FragPos);
	vec3 tangentViewPos = TBN * fs_in.cameraPos;
	vec3 tangentFragPos = TBN * fs_in.FragPos;
	vec3 tangentLightPos = TBN * lightD.pos;
	vec3 tangentViewDir = normalize(tangentViewPos - tangentFragPos);
	vec3 tangentLightDir =  normalize(tangentLightPos - tangentFragPos);
	vec2 texCoords = fs_in.UVCoord;
	//ParallaxMapping
	if(heightMapFlag)
	{
		viewDir = tangentViewDir;
		vec2 texCoords = ParallaxMapping(fs_in.UVCoord,viewDir);
		if(texCoords.x > 1.0 || texCoords.y > 1.0 || texCoords.x < 0.0 || texCoords.y < 0.0)
			discard;
	}


	vec3 finalColor = vec3(0,0,0);
	vec3 normal = texture(material.normal,texCoords).rgb;
		 normal = normalize(normal * 2.0 - 1.0);  

	normal = normalize(TBN * normal);
	vec3 unitNormal = normalize(normal);


	finalColor += CalcLightDirectional(lightD,unitNormal,viewDir);
//finalColor += CalcLightDirectional(lightD,tangentLightDir,unitNormal,viewDir,texCoords);
	FragColor = vec4(finalColor,1.0);
	
	float brightness = dot(finalColor,vec3(0.2126,0.7152,0.0722));
	if(brightness>1.0)
		BrightColor = vec4(finalColor,1.0f);
	else
		BrightColor = vec4(0,0,0,1.0f);

		finalColor = vec3(1,1,1);
		BrightColor = vec4(1,1,1,0);

	FragColor = vec4(finalColor,1.0);


}