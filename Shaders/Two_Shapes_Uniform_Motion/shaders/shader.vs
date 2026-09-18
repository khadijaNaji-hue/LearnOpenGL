#version 330 core

layout ( location = 0 ) in vec3 apos;
layout ( location = 1 ) in vec3 acolor;

out vec3 ourcolor ;
uniform float ourpos;
void main ()
{
    gl_Position = vec4(apos , 1.0) + vec4(ourpos,0.0,0.0,1.0) ; 
    ourcolor = acolor ;
}