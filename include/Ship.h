#pragma once
#include "Types.h"

#include <vector>


class Ship : public GameObject
{
public:

public:
	enum class State
	{
		Thrust,
		Idle,
		Brake,
		Landed
	};

	Ship(Game *pGame, glm::vec2 initialPosition, TriangleRenderer *pRenderer, QuadRenderer *pQuadRenderer);
	~Ship();

	void Update(float dt) override;
	void Render() override;

	void Reset() { 
		m_position = glm::vec2(400.0f, 400.0f);
		m_velocity = glm::vec2(0.0f, 0.0f);
		m_rotation = 0.0f;
	}
private:
	void ProcessInput(float dt);

	glm::vec2 m_position;
	glm::vec2 m_velocity;
	float m_rotation;

	TriangleRenderer * m_pRenderer = nullptr;
	QuadRenderer *m_pQuadRenderer = nullptr;
	Game* m_pGame;
	State m_state;
	std::vector<VertexData> m_vertices;

	
	
};