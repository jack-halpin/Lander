#include "Game.h"
#include "Ship.h"
#include <iostream>
#include <GLFW/glfw3.h>



#define SHIP_SIZE 150.0f

Game::Game(int width, int height)
	: m_width(width),
	m_height(height)
{
}

Game::~Game() 
{
	delete s;
	delete m_pRenderer;
	delete m_pPlayer;
};

void Game::Initialize()
{
	// Setup Triangle Renderer

	//TODO: Set relative paths here
	s = new Shader("../../src/shaders/triangle_vertex.vs", "../../src/shaders/triangle_fragment.fs");
	m_pRenderer = new TriangleRenderer(s);
	m_pRenderer->Initialize();
	m_pRenderer->SetSize(m_width, m_height);

	m_pQuadRenderer = new QuadRenderer(s);
	m_pQuadRenderer->Initialize();
	m_pQuadRenderer->SetSize(m_width, m_height);

	// Calculate center for triangle
	float startX = (m_width / 2) - (SHIP_SIZE / 2);
	float startY = (m_height / 2) - (SHIP_SIZE / 2);

	m_pPlayer = new Ship(this, glm::vec2(startX, startY), m_pRenderer, m_pQuadRenderer);

	// Load Level


	// Set default values
}

void Game::Update(float dt) 
{
	m_pPlayer->Update(dt);
	m_pPlayer->Render();
}

void Game::ProcessInput(int key, int scancode, int action, int mode)
{
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
			keys[key] = false;
	}

	if (keys[GLFW_KEY_S])
		m_pPlayer->Reset();
}