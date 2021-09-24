#pragma once

#include "Shader.h"

#include <vector>


class LineRenderer
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
    LineRenderer(Shader *pShader);
	void Flush();
	void Initialize();
	void SetSize(int x, int y);
    void Add(glm::vec2 position, glm::vec3 colour);

public:
	unsigned int m_vao, m_vbo;
	Shader *m_pShader;
	std::vector<VertexData> m_vertices;
};
