	#type vertex
	#version 330 core
	
	layout(location = 0) in vec3 a_Position;
	layout (location = 2) in vec2 aTexCoords;
	
	
	
	uniform mat4 u_ViewProjection;
	uniform mat4 u_Transform;
	out vec3 v_Position;
	out vec2 TexCoords;
	
	uniform int a_EntityID;
	flat out  int v_EntityID;
	
	void main()
	{
	
		v_EntityID = a_EntityID;
		 TexCoords = aTexCoords;
		v_Position = a_Position;
		gl_Position =u_ViewProjection*vec4(a_Position, 1.0);	
	}


	#type fragment
	#version 330 core
	
	layout(location = 0) out vec4 color;
	
	layout(location = 1) out int color2;
	
	in vec3 v_Position;
	in vec2 TexCoords;
	
	flat in  int v_EntityID;
	
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
	uniform vec3 u_Color;
	void main()
	{
	 vec3 albedo     = texture(material.albedo, TexCoords).rgb;
		color = vec4(albedo, 1.0);
	
	color2 = v_EntityID;
	}
	
