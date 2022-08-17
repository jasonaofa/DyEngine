#version 330 core
out vec4 FragColor;
in vec2 TexCoords;

uniform sampler2D depthMap;



void main()
{             
//    vec2 depthValue = texture(depthMap, TexCoords).rg;
//    FragColor = vec4(vec3(depthValue,0), 1.0); 

    FragColor = texture(depthMap, TexCoords); 

}