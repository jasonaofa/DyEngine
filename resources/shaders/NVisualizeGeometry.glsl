#version 330 core

layout(triangles) in;
layout (line_strip, max_vertices = 6) out;

in VS_OUT{
	vec3 normal;
}gs_in[];

const float MAGNITUDE = 0.2;

uniform mat4 projection;

void GenerateLine(int index)
{
    gl_Position = projection * gl_in[index].gl_Position;
    //输出一个顶点，此时先把定点画出来
    EmitVertex();
    gl_Position = projection * (gl_in[index].gl_Position+vec4(gs_in[index].normal,0.0)*MAGNITUDE);
    //再输出一个顶点，此时的顶点XY加上了法线的XY
    EmitVertex();
    //结束一个图元的输出
    EndPrimitive();
}

void main()
{
    //因为我们in的是一个triangles，有三个顶点。
    GenerateLine(0); // 第一个顶点法线
    GenerateLine(1); // 第二个顶点法线
    GenerateLine(2); // 第三个顶点法线
}
