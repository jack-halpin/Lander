#include "TriangleRenderer.h"


#define MAX_VERTICES 3 * 1000

TriangleRenderer::TriangleRenderer(Shader *pShader)
	: m_pShader(pShader)
{

}

void TriangleRenderer::Add(std::vector<VertexData> &data)
{
	for (auto&& d : data)
	{
		m_vertexData.push_back(d);
	}
}

void TriangleRenderer::Render()
{
	GLenum test = glGetError();

	m_pShader->use();
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, m_vertexData.size() * sizeof(VertexData), &m_vertexData[0]);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);

	m_vertexData.clear();
}

void TriangleRenderer::Render(float x, float y, float height, float width, float rotation, glm::vec3 colour, bool bRotateInPlace)
{
	m_pShader->use();
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(x, y, 0.0f));

	if (bRotateInPlace)
	{
		model = glm::translate(model, glm::vec3(0.5f * width, 0.5f * height, 0.0f)); // move origin of rotation to center of quad
		model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f)); // then rotate
		model = glm::translate(model, glm::vec3(-0.5f * width, -0.5f * height, 0.0f)); // move origin back
	}
	else
	{
		model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f)); // then rotate
	}

	model = glm::scale(model, glm::vec3(width, height, 1.0f));

	m_pShader->setMat4("transform", model);
	m_pShader->setVec3("uColour", colour);
	

	glBindVertexArray(m_vao);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);
}

void TriangleRenderer::SetSize(int x, int y)
{
	m_pShader->use();
    glm::mat4 perspective = glm::ortho(0.0f, static_cast<float>(x),
        0.0f, static_cast<float>(y), -1.0f, 100.0f);
	m_pShader->setMat4("perspective", perspective);
}

void TriangleRenderer::Initialize()
{
	GLenum test = glGetError();

	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);

	glBindVertexArray(m_vao);

	std::vector<VertexData> data{
		{10.0f, 10.0f, 0.0f},
		{50.0f, 100.0f, 0.0f },
		{100.0f, 10.0f, 0.0f}
	};

	// Bind to the buffer. When we bind to the buffer, any future buffer manipulation calls
	// we make will be done on the buffer we have bound to. NOTE: we can bind to one buffer of each type
	// In this case we are using the GL_ARRAY_BUFFER type
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, 1024 * sizeof(VertexData), nullptr, GL_DYNAMIC_DRAW);
	test = glGetError();
	// Now we tell OpenGL how to interpret the vertex data in this VBO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	test = glGetError();

	// The buffer and the vertex attributes have been bound to VAO. We can unbind now.
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	test = glGetError();

}
