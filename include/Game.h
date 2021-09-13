#pragma once

#include "TriangleRenderer.h"
#include "QuadRenderer.h"

class GameObject {
public:
	virtual void Update(float dt) = 0;
	virtual void Render() = 0;
	virtual void Reset() = 0;
};

class Game
{
	typedef bool Keys[1024];
public:
	Game(int width, int height);
	~Game();

public:
	void Initialize();
	void Update(float dt);
	void ProcessInput(int key, int scancode, int action, int mode);
	
	Keys keys;
private:
	int m_width, m_height;
	float m_rotation;
	TriangleRenderer *m_pRenderer = nullptr;
	QuadRenderer *m_pQuadRenderer = nullptr;
	Shader *s;
	GameObject *m_pPlayer;
};