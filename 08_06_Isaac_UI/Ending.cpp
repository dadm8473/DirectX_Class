#include "DXUT.h"
#include "Ending.h"


Ending::Ending()
{
}


Ending::~Ending()
{
}

void Ending::Start()
{
	renderer = new CSpriteRenderer(L"Ending", L"Assets/Images/UI/Ending", L"png", false);

	g_Game.TimeScore = 1000;
	ScoreBoard * score = new ScoreBoard;
	score->position = { -100, -110 };
	score->fRot = 20;

	scale = { 2.5,2.5 };
}

void Ending::Update(float deltaTime)
{
	CGameObject::Update(deltaTime);

	if (g_Game.m_Input.KeyDown(VK_RETURN))
	{
		g_OpenScene->bNextScene = true;
	}
}
