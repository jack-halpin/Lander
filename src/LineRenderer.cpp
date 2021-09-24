#include "LineRenderer.h"


#define MAX_LINES 100

LineRenderer::LineRenderer(Shader *pShader)
	: m_pShader(pShader)
{

}

void LineRenderer::Flush()
{
	m_pShader->use();	
	glBindVertexArray(m_vao);
    
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    glBufferSubData(GL_ARRAY_BUFFER, 0, m_vertices.size() * sizeof(VertexData), &m_vertices[0]);

	glDrawArrays(GL_LINES, 0, m_vertices.size());
	glBindVertexArray(0);
    
    m_vertices.clear();
}

void LineRenderer::SetSize(int x, int y)
{
	m_pShader->use();
    glm::mat4 perspective = glm::ortho(0.0f, static_cast<float>(x),
        0.0f, static_cast<float>(y), -1.0f, 100.0f);
	m_pShader->setMat4("perspective", perspective);
}

void LineRenderer::Add(glm::vec2 position, glm::vec3 colour)
{
    if (m_vertices.size() == MAX_LINES)
    {
        Flush();
    }

    m_vertices.push_back(VertexData{position.x, position.y, colour.x, colour.y, colour.z});
}

void LineRenderer::Initialize()
{
	GLenum test = glGetError();
    
	
	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);

	glBindVertexArray(m_vao);

	// Bind to the buffer. When we bind to the buffer, any future buffer manipulation calls
	// we make will be done on the buffer we have bound to. NOTE: we can bind to one buffer of each type
	// In this case we are using the GL_ARRAY_BUFFER type
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, MAX_LINES * sizeof(VertexData), nullptr, GL_DYNAMIC_DRAW);

	// Now we tell OpenGL how to interpret the vertex data in this VBO
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// The buffer and the vertex attributes have been bound to VAO. We can unbind now.
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}
