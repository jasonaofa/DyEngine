#version 330 core		

in vec2 TexCoords;
out vec4 FragColor;
uniform sampler2D screenTexture;
uniform sampler2D bloomBlur;
uniform float exposure;


void main()
{
    //TODO 先关了gamma和HDR，因为开了之后颜色会变浅、灰
    const float gamma =1;
    vec3 hdrColor = texture(screenTexture,TexCoords).rgb;
    vec3 bloomColor = texture(bloomBlur, TexCoords).rgb;
    hdrColor += bloomColor; // additive blending
    
    // exposure tone mapping
    vec3 toneMapped = vec3(1.0f) - exp(-hdrColor * exposure);
     //FragColor = vec4(toneMapped, 1.0);

    vec3 col = pow(toneMapped,vec3(1.0/gamma));
    FragColor = vec4(col,1);

}
