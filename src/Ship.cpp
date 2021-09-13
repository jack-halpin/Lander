#include "TriangleRenderer.h"
#include "QuadRenderer.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>
#include "Game.h"
#include "Ship.h"

#define ROTATION_VELOCITY  60.0f
#define THRUST_VELOCITY 0.3f
#define GRAVITY 0.125f
#define SHIP_SIZE 150.0f

Ship::Ship(Game *pGame, glm::vec2 initialPosition, TriangleRenderer *pRenderer, QuadRenderer *pQuadRenderer)
	: m_pGame(pGame)
	, m_position(initialPosition)
	, m_pRenderer(pRenderer)
	, m_pQuadRenderer(pQuadRenderer)
	, m_state(State::Idle)
	, m_velocity(0.0f, 0.0f)
{
	m_rotation = 0.0f;
}

Ship::~Ship()
{

}

void Ship::Update(float dt) 
{
	ProcessInput(dt);


	

	switch (m_state) 
	{
	case State::Idle:
		m_velocity.y += (GRAVITY * dt);
		break;
	case State::Thrust:
		float val = glm::cos(90.0f);
		m_velocity.x += glm::cos(glm::radians(90.0f - m_rotation)) * (THRUST_VELOCITY * dt);
		m_velocity.y -= glm::sin(glm::radians(90.0f + m_rotation)) * (THRUST_VELOCITY * dt);
		
		break;
	}

	//m_position.x += m_velocity.x;
	//m_position.y += m_velocity.y;
	//if (m_position.y >= 600 - (SHIP_SIZE + 1))
	//{
	//	// This needs to be a proper collision check
	//	m_state = State::Landed;
	//	m_position.y = 600 - (SHIP_SIZE + 1);
	//	m_velocity.x = 0.0f;
	//	m_velocity.y = 0.0f;
	//}
	//

	

}

void Ship::Render()
{
	m_pRenderer->Render(m_position.x, m_position.y, SHIP_SIZE, SHIP_SIZE, m_rotation, glm::vec3(1.0f));
	m_pQuadRenderer->Render(m_position.x, m_position.y, SHIP_SIZE, SHIP_SIZE, m_rotation, glm::vec3(1.0f));

	glm::vec2 shipPosition = m_position;
	if (m_state == State::Idle) {
		// Calculate position for small triangle
		float flameSize = SHIP_SIZE / 2;
		glm::vec4 flamePosition(shipPosition, 0.0f, 1.0f);

		float cos = glm::cos(glm::radians(m_rotation));
		float sin = glm::sin(glm::radians(m_rotation));

		float dx = 0;
		float dy = SHIP_SIZE;


		glm::mat4 model = glm::mat4(1.0f);

#define SHIP_HALF SHIP_SIZE/2
		model = glm::translate(model, glm::vec3(SHIP_HALF, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(m_position.x, m_position.y, 0.0f)); // first translate (transformations are: scale happens first, then rotation, and then final translation happens; reversed order)
		model = glm::translate(model, glm::vec3(0.5f * SHIP_SIZE, 0.5f * SHIP_SIZE, 0.0f)); // move origin of rotation to center of quad
		model = glm::rotate(model, glm::radians(m_rotation), glm::vec3(0.0f, 0.0f, 1.0f)); // then rotate
		model = glm::translate(model, glm::vec3(-0.5f * SHIP_SIZE, -0.5f * SHIP_SIZE, 0.0f)); // move origin back
		model = glm::scale(model, glm::vec3(SHIP_SIZE, SHIP_SIZE, 1.0f)); // last scale

		model = glm::scale(model, glm::vec3(SHIP_SIZE, SHIP_SIZE, 1.0f)); // last scale

		glm::vec4 point(0.0f, 0.0f, 0.f, 1.0f);
		point = model * point;

		std::cout << "Angle : " << m_rotation << std::endl;

		std::cout << "Cos values: " << cos * dy << std::endl;
		std::cout << "Sin values: " << sin * dx << std::endl;

		flamePosition.x = cos * dx - sin * dy + point.x;
		flamePosition.y = cos * dy + sin * dx + point.y;
		
		flamePosition = point;

		m_pQuadRenderer->Render(flamePosition.x, flamePosition.y, SHIP_SIZE, SHIP_SIZE, m_rotation, glm::vec3(1.0f, 0.0f, 0.0f));
	}
}

void Ship::ProcessInput(float dt)
{
	// Left and Right
	if (m_state != State::Landed)
	{
		if (m_pGame->keys[GLFW_KEY_A])
			m_rotation -= ROTATION_VELOCITY * dt;
		if (m_pGame->keys[GLFW_KEY_D])
			m_rotation += ROTATION_VELOCITY * dt;
	}
	

	if ((m_pGame->keys[GLFW_KEY_W]))
		m_state = State::Thrust;
	else
		m_state = State::Idle;
}