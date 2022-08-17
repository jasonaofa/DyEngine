#version 330 core		

out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;
const int radius = 6;
uniform bool horizontal;
uniform float weight[5] = float[] (0.227027, 0.1945946, 0.1216216, 0.054054, 0.016216);
void main()
{
	//得到每一个纹素的尺寸
  vec2 tex_offset = 1.0/textureSize(screenTexture,0);
  vec3 result = texture(screenTexture,TexCoords).rgb * weight[0];
  if(horizontal)
  {
	for(int i = 1;i<radius;++i)
	{
	//如果水平，那就Y =0
		result += texture(screenTexture,TexCoords+vec2(tex_offset.x*i,0.0)).rgb *weight[i];
		result += texture(screenTexture,TexCoords-vec2(tex_offset.x*i,0.0)).rgb *weight[i];
	}
  }
  else
  {
	for(int i =1;i<radius;++i)
	{
		result += texture(screenTexture,TexCoords+vec2(0.0,tex_offset.x*i)).rgb *weight[i];
		result += texture(screenTexture,TexCoords-vec2(0.0,tex_offset.x*i)).rgb *weight[i];
	}
  }
       FragColor = vec4(result, 1.0);
}