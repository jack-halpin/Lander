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
	delete m_pSimpleShader;
	delete m_pLineShader;
	delete m_pRenderer;
	delete m_pPlayer;
	delete m_pLevel;
	delete m_pQuadRenderer;
	delete m_pLineRenderer;
};

void Game::Initialize()
{
	// Setup Triangle Renderer

	//TODO: Set relative paths here
	m_pSimpleShader = new Shader("../../src/shaders/triangle_vertex.vs", "../../src/shaders/triangle_fragment.fs");
	m_pRenderer = new TriangleRenderer(m_pSimpleShader);
	m_pRenderer->Initialize();
	m_pRenderer->SetSize(m_width, m_height);
    
    m_pRenderer->Render(100, 100, 100, 100, 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));

	m_pQuadRenderer = new QuadRenderer(m_pSimpleShader);
	m_pQuadRenderer->Initialize();
	m_pQuadRenderer->SetSize(m_width, m_height);

    m_pLineShader = new Shader("../../src/shaders/line_vertex.vs", "../../src/shaders/line_fragment.fs");

	m_pLineRenderer = new LineRenderer(m_pLineShader);
	m_pLineRenderer->Initialize();
	m_pLineRenderer->SetSize(m_width, m_height);

	// Calculate center for triangle
	float startX = (m_width / 2) - (SHIP_SIZE / 2);
	float startY = (m_height / 2) - (SHIP_SIZE / 2);

	m_pPlayer = new Ship(this, glm::vec2(startX, startY), m_pRenderer, m_pQuadRenderer);

	// Load Level
	m_pLevel = new Level("../../src/levels/level-1.txt", m_pLineRenderer);
	m_pLevel->LoadLevel();

	// Set default values
}

void Game::Update(float dt) 
{
    m_pLevel->Render();

	m_pPlayer->Update(dt);
	
	// Check collisions between new player position and level coordinates



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
