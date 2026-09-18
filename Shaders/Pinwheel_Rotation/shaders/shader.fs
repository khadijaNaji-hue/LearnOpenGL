#version 330 core 

in vec3 ourcolor ;

out vec4 FragColor ;

uniform float ourGColor; // we set this variable in the OpenGL code.
uniform float ourRColor; // we set this variable in the OpenGL code.

void main ()
{
    FragColor = vec4(ourcolor , 1.0 ) + vec4(ourRColor , ourGColor, 0.0 , 0.0);
}