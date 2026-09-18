#version 330 core

layout ( location = 0 ) in vec3 apos;
layout ( location = 1 ) in vec3 acolor;
layout ( location = 2 ) in float offset;

out vec3 ourcolor ;

uniform float angle;

void main ()
{
    float Angle = angle + (offset * ((60.0f / 180.0f)* 3.14159f) ) ;
    float x_new = apos.x * cos(Angle) - apos.y * sin(Angle);
    float y_new = apos.x * sin(Angle) + apos.y * cos(Angle);
    gl_Position = vec4(x_new, y_new, apos.z, 1.0);
    ourcolor = acolor ;
}

