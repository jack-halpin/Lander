#version 330 core

layout (location = 0) in vec3 aPos;

uniform mat4 transform;
uniform mat4 perspective;

void main()
{
	vec4 model = vec4(aPos.x, aPos.y, aPos.z, 1.0f);
	gl_Position = perspective * transform * model;
}