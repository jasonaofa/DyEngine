#version 330 core		
layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;
					  
//从顶点的纹理坐标传过来的数据
//in vec3 vertexColor;
//in vec2 texCoord;
in VS_OUT
{
	vec3 FragPos;
	vec2 UVCoord;
	vec3 Normal;
	vec4 FragPosLightSpace;
}fs_in;


//in vec3 Normal;
//in vec3 FragPos;
//in vec2 UVCoord;

struct Material
{
 vec3 ambient;
 sampler2D albedo;
 //metallic = specular
 sampler2D metallic;
 sampler2D emission;
 sampler2D roughness;
 float shininess;
};

struct DirectionalLight
{
	 vec3 dirToLight;
	 vec3 color;
	 vec3 pos;
	 float intensity;
};

struct PointLight
{
	float constant;
	float linear;
	float quadratic;
	vec3 dirToLight;
	vec3 color;
	vec3 pos;
};

struct SpotLight
{
	float constant;
	float linear;
	float quadratic;
	vec3 dirToLight;
	vec3 color;
	vec3 pos;
	float cosPhiInner;
	float cosPhiOuter;
};




uniform sampler2D ourTexture;//自定义的全局sampler2D 变量中的值，其实是[0,15]这15个整数数字
uniform sampler2D ourFace;
uniform vec3 objColor;//objColor == albedo
uniform vec3 ambientColor;
uniform samplerCube skybox;
uniform sampler2D shadowMap;

uniform vec3 cameraPos;

uniform Material material;
uniform DirectionalLight lightD;
uniform PointLight lightP0;
uniform SpotLight spotLight;
//HDR
uniform float exposure;

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


//	shadow = currentDepth -0.001f> closestDepth  ? 1.0 : 0.0;
	    if(projCoords.z > 1.0)
        shadow = 0.0;

    return shadow;
}




//平行光函数
vec3 CalcLightDirectional(DirectionalLight light, vec3 unitNormal,vec3 dirToCamera)
{
	//diffuse max(0,dot(n,l)) 
	float diffuseIntensity = max(0,dot(unitNormal,light.dirToLight));
	vec3 diffuseColor = diffuseIntensity * light.color * texture(material.albedo,fs_in.UVCoord).rgb;
	//specular dot(R,V)
	vec3 refDir = reflect(-light.dirToLight,unitNormal);
	float specularIntensity = pow(max(0,dot(refDir,dirToCamera)),material.shininess);
	vec3 specularColor = specularIntensity * light.color*0.5f;
//	vec3 specularColor = specularIntensity * light.color * texture(material.specular,fs_in.UVCoord).rgb;
	//ref
	vec3 refMask = texture(material.roughness,fs_in.UVCoord).xyz;
	vec3 ViewDirToFrag = normalize(fs_in.FragPos - cameraPos);
	vec3 R = reflect(ViewDirToFrag,unitNormal);
	vec3 refColor = texture(skybox,R).xyz * refMask * light.color ;
	//ambient
	vec3 ambient =  material.ambient*texture(material.albedo,fs_in.UVCoord).rgb* light.color;
	float shadow = ShadowCalculation(fs_in.FragPosLightSpace);
	//TODO 反射不能够和漫反射共存，不知道原因
	vec3 result = ((diffuseColor+specularColor)*(1-shadow)+ambient)* light.intensity;
//	vec3 result = diffuseColor ;
	return result;
}

//点光源函数
vec3 CalcLightPoint(PointLight light,vec3 unitNormal,vec3 dirToCamera )
{
	//attenuation
	float dist = length(light.pos - fs_in.FragPos);
	float attenuation = 1.0/(light.constant+light.linear*dist+light.quadratic*(dist*dist));
	//diffuse
	float diffuseIntensity = max(0,dot(unitNormal,normalize(light.pos - fs_in.FragPos))) * attenuation ;
	vec3 diffuseColor = diffuseIntensity * light.color * texture(material.albedo,fs_in.UVCoord).rgb;
	//specular
	vec3 ref = reflect(-normalize(light.pos - fs_in.FragPos),unitNormal);
	float specularIntensity = pow(max(0,dot(ref,dirToCamera)),material.shininess) * attenuation;
	vec3 specularColor = specularIntensity * light.color * texture(material.metallic,fs_in.UVCoord).rgb;

	vec3 result = diffuseColor + specularColor ;
	return result;
}
//Spot函数
vec3 CalcLightSpot(SpotLight light,vec3 unitNormal,vec3 dirToCamera )
{
	//attenuation
	float dist = length(light.pos - fs_in.FragPos);
	float attenuation = 1.0/(light.constant+light.linear*dist+light.quadratic*(dist*dist));
	float spotRatio;
		
	float cosTheta = dot(normalize(fs_in.FragPos - light.pos),-light.dirToLight);//	if(cosTheta >spotLight.cosPhiInner)
	if(cosTheta >light.cosPhiInner)
	{
		spotRatio = 1.0f;
	}
	else if	(cosTheta >light.cosPhiOuter)
	{
		spotRatio = 1.0f - (cosTheta - light.cosPhiInner) / (light.cosPhiOuter - light .cosPhiInner);
	}
	else
	{
		spotRatio = 0;
	}
	//diffuse
	float diffuseIntensity = max(0,dot(unitNormal,normalize(light.pos - fs_in.FragPos))) * attenuation ;
	vec3 diffuseColor = diffuseIntensity * light.color * texture(material.albedo,fs_in.UVCoord).rgb;
	//specular
	vec3 ref = reflect(-normalize(light.pos - fs_in.FragPos),unitNormal);
	float specularIntensity = pow(max(0,dot(ref,dirToCamera)),material.shininess) * attenuation;
	vec3 specularColor = specularIntensity * light.color * texture(material.metallic,fs_in.UVCoord).rgb;
	vec3 result;
	if(cosTheta >light.cosPhiInner)
	{
		result = (diffuseColor + specularColor) *spotRatio   ;	
	}
	else if	(cosTheta >light.                    cosPhiOuter)
	{
		result = (diffuseColor + specularColor ) *spotRatio  ;	
	}
	else
	{
	//outside
		result = (diffuseColor + specularColor)  *spotRatio  ;	
	}
	return result;
}

const float offset = 1.0 / 300.0;  
void main()
{
//	vec4 refMask = texture(material.reflection,UVCoord);
//	vec3 ViewDirToFrag = normalize(FragPos - cameraPos);
//	vec3 R = reflect(ViewDirToFrag, normalize(Normal));
	vec3 finalColor = vec3(0,0,0);
	vec3 unitNormal = normalize(fs_in.Normal);
	vec3 dirToCamera = normalize(cameraPos - fs_in.FragPos);
	finalColor += CalcLightDirectional(lightD,unitNormal,dirToCamera);
//	finalColor += CalcLightPoint(lightP0,unitNormal,dirToCamera);
//	finalColor += CalcLightPoint(lightP1,unitNormal,dirToCamera);
//	finalColor += CalcLightPoint(lightP2,unitNormal,dirToCamera);
//	finalColor += CalcLightPoint(lightP3,unitNormal,dirToCamera);
//	finalColor += CalcLightSpot(spotLight,unitNormal,dirToCamera);
//	vec3 refColor = texture(skybox, R).rgb * refMask.rgb;

	float shadow = 1-ShadowCalculation(fs_in.FragPosLightSpace);
	vec3 shadowVec3 = vec3(shadow,shadow,shadow);



	float brightness = dot(finalColor,vec3(0.2126,0.7152,0.0722));
	if(brightness>1.0)
		BrightColor = vec4(finalColor,1.0f);
	else
		BrightColor = vec4(0,0,0,1.0f);
	FragColor = vec4(finalColor,1.0);


//	FragColor = vec4(shadowVec3,1.0);


//	finalColor +=refColor;
//	FragColor = vec4(finalColor,1.0);

}



//	float dist = length(lightPos - FragPos);
//	float attenuation = 1.0/(pointLight.constant+pointLight.linear*dist+pointLight.quadratic*(dist*dist));
//	vec3 lightDir = normalize(lightPos - FragPos);
////	vec3 lightDir = lightDirUniform;
//	float LdotN = max(0,dot(lightDir,Normal));
//
//
//	vec3 reflectionDir = reflect(-lightDir,Normal);
//	vec3 cameraVec = normalize(cameraPos - FragPos);
//	float specularAmount = pow(max(dot(reflectionDir,cameraVec),0),material.shininess);
//
//	//diffuse
//	vec3 diffuse =texture(material.diffuse,UVCoord).rgb * LdotN * lightColor ;
//	//vec3 diffuse = texture(material.diffuse,UVCoord).rgb;
//
//	//specular
//	//vec3 specular = specularAmount * lightColor * material.specular;
//	vec3 specular = specularAmount * lightColor * texture(material.specular,UVCoord).rgb;
//	//ambient
//	vec3 ambient =  ambientColor*material.ambient*texture(material.diffuse,UVCoord).rgb;
//	//albedo
//	vec3 albedo = objColor;
//	//emission
//	vec3 emission = texture(material.emission,UVCoord).rgb;
//	//spotLight
//	float spotRatio;
//	float cosTheta = dot(normalize(FragPos - lightPos),-1 * lightDirUniform);
//	if(cosTheta >spotLight.cosPhiInner)
//	{
//		spotRatio = 1.0f;
//	}
//	else if	(cosTheta >spotLight.cosPhiOuter)
//	{
//		spotRatio = 1.0f - (cosTheta - spotLight.cosPhiInner) / (spotLight.cosPhiOuter - spotLight .cosPhiInner);
//	}
//	else
//	{
//		spotRatio = 0;
//	}
//
//	if(cosTheta >spotLight.cosPhiInner)
//	{
//		FragColor = vec4(( ambient +(diffuse + specular) *spotRatio  ) * albedo  ,1.0f);	
//	}
//	else if	(cosTheta >spotLight.cosPhiOuter)
//	{
//		FragColor = vec4(( ambient +(diffuse + specular ) *spotRatio ) * albedo  ,1.0f);	
//	}
//	else
//	{
//	//outside
//		FragColor = vec4(( ambient +(diffuse + specular)  *spotRatio ) * albedo  ,1.0f);	
//	}
//
//	FragColor = vec4(( ambient +diffuse + specular   ) * albedo * attenuation ,1.0f);
