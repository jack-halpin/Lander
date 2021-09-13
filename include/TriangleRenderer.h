#pragma once

#include "Shader.h"

#include <vector>


class TriangleRenderer
{
	struct VertexData
	{
		float x;
		float y;
		float red;
		float blue;
		float green;
	};

public:
	TriangleRenderer(Shader *pShader);
	void Render(float x, float y, float height, float width, float rotation, glm::vec3 colour, bool bRotateInPlace = true);
	void Initialize();
	void SetSize(int x, int y);

public:
	unsigned int m_vao, m_vbo;
	Shader *m_pShader;
	std::vector<float> m_vertices;
};