#version 330 core 

in vec3 ourcolor ;
in vec2 ourTexture ;

out vec4 FragColor ;

uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;

void main ()
{
    FragColor = mix(texture(ourTexture1 , ourTexture), texture(ourTexture2 , ourTexture), 0.6) * vec4(ourcolor,1.0) ;
}