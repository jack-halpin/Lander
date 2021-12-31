#pragma once

#include "Shader.h"
#include "Types.h"

#include <vector>


class TriangleRenderer
{
public:
	TriangleRenderer(Shader *pShader);

	void Add(std::vector<VertexData>& data);
	void Render();
	void Render(float x, float y, float height, float width, float rotation, glm::vec3 colour, bool bRotateInPlace = true);
	void Initialize();
	void SetSize(int x, int y);

public:
	unsigned int m_vao, m_vbo;
	Shader *m_pShader;
	std::vector<VertexData> m_vertexData;
};
