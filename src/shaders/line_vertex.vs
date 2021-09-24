#version 330 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec3 aColour;

out vec3 oColour;

uniform mat4 perspective;

void main()
{
    oColour = aColour;
	vec4 model = vec4(aPos.x, aPos.y, 0.0f, 1.0f);
	gl_Position = perspective * model;
}