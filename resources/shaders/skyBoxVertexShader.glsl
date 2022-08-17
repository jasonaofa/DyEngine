#version 330 core
layout (location = 0) in vec3 aPos;

out vec3 TexCoords;

uniform mat4 projection;
uniform mat4 view;


void main()
{
    TexCoords = aPos;
//    TexCoords = aPos;
    vec4 pos = projection * view * vec4(aPos, 1.0);
    //NB: XYWW NOT XYZW，KEEP Z =1.0F DEPTH VALUE = 1.0F;
    gl_Position = pos.xyww;
}