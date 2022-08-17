#version 330 core	
layout(location = 0) in vec3 aPos; 
layout(location = 1) in vec3 aNormal; 
layout(location = 2) in vec2 aUVCoord; 

//out vec3 Normal;
//out vec3 FragPos;
//out vec2 UVCoord;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 lightSpaceMatrix;
out VS_OUT{
	vec3 FragPos;
    vec2 UVCoord;
    vec3 Normal;
	vec4 FragPosLightSpace;
}vs_out;

void main() {
	vs_out.UVCoord = aUVCoord;
	gl_Position =projection * view * model * vec4(aPos, 1.0) ; 
//		gl_Position =lightSpaceMatrix * model * vec4(aPos, 1.0) ; 
	vs_out.FragPos = (model * vec4(aPos, 1.0)).xyz;
	vs_out.Normal = mat3(transpose(inverse(model))) * aNormal;
	vs_out.FragPosLightSpace = lightSpaceMatrix* vec4(vs_out.FragPos,1.0f);
	}