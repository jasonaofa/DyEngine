#version 330 core
out vec4 FragColor;
in vec2 TexCoords;
in vec3 WorldPos;
in vec3 Normal;
in vec4 FragPosLightSpace;

struct Material
{
 sampler2D albedo;
 //metallic = specular
 sampler2D metallic;
 sampler2D normal;
 sampler2D roughness;
 sampler2D aoMap;
};
uniform Material material;

uniform samplerCube prefilterMap;
uniform sampler2D   brdfLUT;  
uniform samplerCube irradianceMap;
uniform sampler2D shadowMap;
uniform float ao;

// lights
//uniform vec3 lightPositions[4];
vec3 lightPositions = 		glm::vec3(0.0f, 0.0f, 10.0f);
//uniform vec3 lightColors[4];
//vec3 lightColors = glm::vec3(150.0f, 150.0f, 150.0f);
//TODO 之后改成结构体
uniform vec3 lightColor;
uniform float lightIntensity;
uniform vec3 lightDir;
uniform vec3 lightPos;
uniform vec3 camPos;



const float PI = 3.14159265359;




vec3 N;
// ----------------------------------------------------------------------------
// Easy trick to get tangent-normals to world-space to keep PBR code simplified.
// Don't worry if you don't get what's going on; you generally want to do normal 
// mapping the usual way for performance anways; I do plan make a note of this 
// technique somewhere later in the normal mapping tutorial.
vec3 getNormalFromMap()
{
    vec3 tangentNormal = texture(material.normal, TexCoords).xyz * 2.0 - 1.0;

    vec3 Q1  = dFdx(WorldPos);
    vec3 Q2  = dFdy(WorldPos);
    vec2 st1 = dFdx(TexCoords);
    vec2 st2 = dFdy(TexCoords);

    vec3 N   = normalize(Normal);
    vec3 T  = normalize(Q1*st2.t - Q2*st1.t);
    vec3 B  = -normalize(cross(N, T));
    mat3 TBN = mat3(T, B, N);

    return normalize(TBN * tangentNormal);
}

//计算阴影
float ShadowCalculation(vec4 fragPosLightSpace)
{
    vec3 normalDir = getNormalFromMap();
    //执行透视除法
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // 变换到[0,1]的范围
    projCoords = projCoords * 0.5 + 0.5;
    // 取得最近点的深度(使用[0,1]范围下的fragPosLight当坐标)
    float closestDepth = texture(shadowMap, projCoords.xy).r;
    //在灯光视角下，每个片元的Z值就是当前片元在灯光视角下的深度
    float currentDepth = projCoords.z;
    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
    float bias = max(0.001 * (1.0 - dot(normalDir, lightDir)), 0.0001);
    for (int x = -3; x <= 3; ++x)
    {
        for (int y = -3; y <= 3; ++y)
        {
            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r;
            shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;
        }
    }
    shadow /= 49.0;

    if (projCoords.z > 1.0)
        shadow = 0.0;

    return shadow;
}






// ----------------------------------------------------------------------------
float DistributionGGX(vec3 N, vec3 H, float roughness)
{
    float a = roughness*roughness;
    float a2 = a*a;
    float NdotH = max(dot(N, H), 0.0);
    float NdotH2 = NdotH*NdotH;

    float nom   = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;

    return nom / denom;
}
// ----------------------------------------------------------------------------
float GeometrySchlickGGX(float NdotV, float roughness)
{
    float r = (roughness + 1.0);
    float k = (r*r) / 8.0;

    float nom   = NdotV;
    float denom = NdotV * (1.0 - k) + k;

    return nom / denom;
}
// ----------------------------------------------------------------------------
float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx2 = GeometrySchlickGGX(NdotV, roughness);
    float ggx1 = GeometrySchlickGGX(NdotL, roughness);

    return ggx1 * ggx2;
}
// ----------------------------------------------------------------------------
vec3 fresnelSchlick(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0);
}
// ----------------------------------------------------------------------------
vec3 fresnelSchlickRoughness(float cosTheta, vec3 F0, float roughness)
{
    return F0 + (max(vec3(1.0 - roughness), F0) - F0) * pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0);
}   
// ----------------------------------------------------------------------------
void main()
{		
    vec3 albedo     = pow(texture(material.albedo, TexCoords).rgb, vec3(2.2));
    float metallic  = texture(material.metallic, TexCoords).r;
    float roughness = texture(material.roughness, TexCoords).r;
    float aoMap = texture(material.aoMap, TexCoords).r;

    N = getNormalFromMap();
    vec3 V = normalize(camPos - WorldPos);
    vec3 R = reflect(-V,N);

    // calculate reflectance at normal incidence; if dia-electric (like plastic) use F0 
    // of 0.04 and if it's a metal, use the albedo color as F0 (metallic workflow)    
    vec3 F0 = vec3(0.04); 
    F0 = mix(F0, albedo, metallic);

    // reflectance equation


    vec3 directLighting = vec3(0);
    {
        // calculate per-light radiance
        vec3 L = normalize(lightDir);
        vec3 H = normalize(V + L);
//        float distance = length(lightPos - WorldPos);
//        float attenuation = 1.0 / (distance * distance);
//        vec3 radiance = lightColors * attenuation;
        vec3 radiance = lightColor*lightIntensity ;

        // Cook-Torrance BRDF
        float NDF = DistributionGGX(N, H, roughness);   
        float G   = GeometrySmith(N, V, L, roughness);      
        vec3 F    = fresnelSchlick(max(dot(H, V), 0.0), F0);
           
        vec3 numerator    = NDF * G * F; 
        float denominator = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0) + 0.0001; // + 0.0001 to prevent divide by zero
        vec3 specular = numerator / denominator;
        
        // kS is equal to Fresnel
        vec3 kS = F;
        // for energy conservation, the diffuse and specular light can't
        // be above 1.0 (unless the surface emits light); to preserve this
        // relationship the diffuse component (kD) should equal 1.0 - kS.
        vec3 kD = vec3(1.0) - kS;
        // multiply kD by the inverse metalness such that only non-metals 
        // have diffuse lighting, or a linear blend if partly metal (pure metals
        // have no diffuse light).
        kD *= 1.0 - metallic;	  

        // scale light by NdotL
        float NdotL = max(dot(N, L), 0.0);        

        // add to outgoing radiance Lo
        directLighting += (kD * albedo / PI + specular) * radiance * NdotL;  // note that we already multiplied the BRDF by the Fresnel (kS) so we won't multiply by kS again
    }

    vec3 indirectLighting = vec3(0);
    {
    //calculate diffuse ambient 
    vec3 ambientF = fresnelSchlickRoughness(max(dot(N, V), 0.0), F0, roughness);

    vec3 kS = ambientF;
    vec3 kD = 1.0- kS;
     kD *= 1.0 - metallic;

    vec3 irradiance = texture(irradianceMap, N).rgb;
    vec3 diffuse = irradiance * albedo;

    //calculate specular ambient 
    const float MAX_REFLECTION_LOD = 0.5;
    vec3 prefilteredColor = textureLod(prefilterMap, R,  roughness * MAX_REFLECTION_LOD).rgb;   
    vec2 envBRDF  = texture(brdfLUT, vec2(max(dot(N, V), 0.0), roughness)).rg;
    vec3 specular = prefilteredColor *(ambientF * envBRDF.x + envBRDF.y);

    vec3 test = texture(brdfLUT,TexCoords).rgb;
    test = textureLod(prefilterMap,WorldPos,1).rgb;

    indirectLighting = (kD*diffuse + specular ) * ao * aoMap;
    }

    float shadow = 1 - ShadowCalculation(FragPosLightSpace);



    //TODO shadow 这样做肯定有问题，先暂且这样，之后做CSM
   vec3 color = (indirectLighting + directLighting) *(shadow+0.2);
    //vec3 color = (indirectLighting + directLighting);

    // HDR tonemapping
    color = color / (color + vec3(1.0));
    // gamma correct
    color = pow(color, vec3(1.0/2.2)); 

   FragColor =vec4(color,1);
 
   //FragColor = vec4(N,1);

}