#include "TriangleRenderer.h"
#include "QuadRenderer.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>
#include "Game.h"
#include "Ship.h"

#define ROTATION_VELOCITY  60.0f
#define THRUST_VELOCITY 0.9f
#define GRAVITY 0.6f
#define SHIP_SIZE 50.0f

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
		m_velocity.y -= (GRAVITY * dt);
		break;
	case State::Thrust:
		m_velocity.x += glm::cos(glm::radians(90.0f + m_rotation)) * (THRUST_VELOCITY * dt);
		m_velocity.y += glm::sin(glm::radians(90.0f + m_rotation)) * (THRUST_VELOCITY * dt);
		break;
	}

	m_position.x += m_velocity.x;
	m_position.y += m_velocity.y;
	if (m_position.y <= 1)
	{
		// This needs to be a proper collision check
		m_state = State::Landed;
		m_position.y = 1.0f;
		m_velocity.x = 0.0f;
		m_velocity.y = 0.0f;
	}
}

void Ship::Render()
{
	m_pRenderer->Render(m_position.x, m_position.y, SHIP_SIZE, SHIP_SIZE, m_rotation, glm::vec3(1.0f));

	glm::vec2 shipPosition = m_position;
	if (m_state == State::Thrust) {
        // NOTE: All this code is incredibly complicated and only written because
        // I wanted to try understand the geometry a bit better. Easiest way would
        // be to define the thrust vertices beforehand and just draw them with the
        // same transformation


		// Calculate position for small triangle
		// Figure out where the top left point of the big triangle currently is
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(m_position.x, m_position.y, 0.0f));

		model = glm::translate(model, glm::vec3(0.5f * SHIP_SIZE, 0.5f * SHIP_SIZE, 0.0f)); // move origin of rotation to center of quad
		model = glm::rotate(model, glm::radians(m_rotation), glm::vec3(0.0f, 0.0f, 1.0f)); // then rotate
		model = glm::translate(model, glm::vec3(-0.5f * SHIP_SIZE, -0.5f * SHIP_SIZE, 0.0f)); // move origin back
		model = glm::scale(model, glm::vec3(SHIP_SIZE, SHIP_SIZE, 1.0f)); // last scale
		glm::vec4 topLeft(0.0f, 0.0f, 0.0f, 1.0f);

		// Transform the topLeft
		glm::vec4 newPoint = model * topLeft;

		float flameSize = SHIP_SIZE * 0.75;
		glm::vec4 flamePosition(shipPosition, 0.0f, 1.0f);
        
		float cos = glm::cos(glm::radians(m_rotation));
		float sin = glm::sin(glm::radians(m_rotation));

		float dx = (SHIP_SIZE - flameSize) / 2;
		float dy = -flameSize - 1; // + 1 so the two triangles don't overlap

        // Offset from big ship
		flamePosition.x = cos * dx - sin * dy + newPoint.x;
		flamePosition.y = cos * dy + sin * dx + newPoint.y;

        // Since it's rotated 180 about it's top left, need to add offset
        flamePosition.x += cos * flameSize - sin * flameSize;
        flamePosition.y += cos * flameSize + sin * flameSize;

		m_pRenderer->Render(flamePosition.x, flamePosition.y, flameSize, flameSize, 180.0f + m_rotation, glm::vec3(1.0f, 0.0f, 0.0f), false);
	}
}

void Ship::ProcessInput(float dt)
{
	// Left and Right
	if (m_state != State::Landed)
	{
		if (m_pGame->keys[GLFW_KEY_A])
			m_rotation += ROTATION_VELOCITY * dt;
		if (m_pGame->keys[GLFW_KEY_D])
			m_rotation -= ROTATION_VELOCITY * dt;
	}
	

	if ((m_pGame->keys[GLFW_KEY_W]))
		m_state = State::Thrust;
	else
		m_state = State::Idle;
}
