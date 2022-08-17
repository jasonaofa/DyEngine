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
    //���һ�����㣬��ʱ�ȰѶ��㻭����
    EmitVertex();
    gl_Position = projection * (gl_in[index].gl_Position+vec4(gs_in[index].normal,0.0)*MAGNITUDE);
    //�����һ�����㣬��ʱ�Ķ���XY�����˷��ߵ�XY
    EmitVertex();
    //����һ��ͼԪ�����
    EndPrimitive();
}

void main()
{
    //��Ϊ����in����һ��triangles�����������㡣
    GenerateLine(0); // ��һ�����㷨��
    GenerateLine(1); // �ڶ������㷨��
    GenerateLine(2); // ���������㷨��
}
