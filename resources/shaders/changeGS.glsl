#version 330 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in change_TBN{
	vec3 FragPos;
    vec2 UVCoord;
    vec3 Normal;
	vec4 FragPosLightSpace;
    mat4 projection;
    mat3 normalMatrix;
    vec3 cameraPos;
    vec3 lightDirection;
}gs_in[];

out change_TBN{
    vec3 FragPos;
    vec2 UVCoord;
    vec3 Normal;
    vec4 FragPosLightSpace;
    vec3 cameraPos;
    vec3 lightDirection;
    vec3 T;
    vec3 B;
}gs_out;

// Default main function
void main()
{
    // Edges of the triangle
    vec3 edge1 = gl_in[1].gl_Position.xyz - gl_in[0].gl_Position.xyz;
    vec3 edge2 = gl_in[2].gl_Position.xyz - gl_in[0].gl_Position.xyz;
    // Lengths of UV differences
    vec2 deltaUV1 = gs_in[1].UVCoord - gs_in[0].UVCoord;
    vec2 deltaUV2 = gs_in[2].UVCoord - gs_in[0].UVCoord;
        // one over the determinant
    float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);
    vec3 tangent,bitangent;
    tangent.x =f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
    tangent.y =f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
    tangent.z =f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);


    bitangent.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
    bitangent.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
    bitangent.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);

    vec3 T = normalize(gs_in[0].normalMatrix * tangent);
    vec3 B = normalize(gs_in[0].normalMatrix * bitangent);
//    vec3 N = normalize(gs_in[0].normalMatrix * cross(edge1, edge0));
//
//    mat3 TBN = mat3(T, B, N);
//    // TBN is an orthogonal matrix and so its inverse is equal to its transpose
//    TBN = transpose(TBN);



    gs_out.T = T;
    gs_out.B = B;
    gl_Position =gs_in[0].projection*gl_in[0].gl_Position;
    gs_out.UVCoord = gs_in[0].UVCoord;
    gs_out.Normal = gs_in[0].Normal;
    gs_out.FragPosLightSpace = gs_in[0].FragPosLightSpace;
    // Change all lighting variables to TBN space
    gs_out.FragPos =  gs_in[0].FragPos;
    gs_out.cameraPos = gs_in[0].cameraPos;
    gs_out.lightDirection = gs_in[0].lightDirection;

    EmitVertex();

    gl_Position = gs_in[1].projection*gl_in[1].gl_Position;

    gs_out.UVCoord = gs_in[1].UVCoord;
    gs_out.Normal = gs_in[1].Normal;
    gs_out.FragPosLightSpace = gs_in[1].FragPosLightSpace;
    // Change all lighting variables to TBN space
    gs_out.FragPos =  gs_in[1].FragPos;
    gs_out.cameraPos = gs_in[1].cameraPos;
    gs_out.lightDirection =gs_in[1].lightDirection;

    EmitVertex();

    gl_Position =gs_in[2].projection* gl_in[2].gl_Position;

    gs_out.UVCoord = gs_in[2].UVCoord;
    gs_out.Normal = gs_in[2].Normal;
    gs_out.FragPosLightSpace = gs_in[2].FragPosLightSpace;
    // Change all lighting variables to TBN space
    gs_out.FragPos =  gs_in[2].FragPos;
    gs_out.cameraPos =gs_in[2].cameraPos;
    gs_out.lightDirection = gs_in[2].lightDirection;

    EmitVertex();

    EndPrimitive();
}