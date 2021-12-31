#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColour;

uniform mat4 perspective;

out vec3 oColour;

void main()
{
	oColour = aColour;
	vec4 model = vec4(aPos.x, aPos.y, aPos.z, 1.0f);
	gl_Position = perspective * model;
}