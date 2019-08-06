#include "DXUT.h"
#include "Title.h"


Title::Title()
{
}


Title::~Title()
{
}

void Title::Start()
{
	// 스프라이트 렌더러 추가
	renderer = new CSpriteRenderer(L"Title", L"Assets/Images/Title", L"png", false);

	position = { 512,384 };
}

void Title::Update(float deltaTime)
{
	CGameObject::Update(deltaTime);

	if (g_Game.m_Input.KeyDown(VK_RETURN))
	{
		g_OpenScene->bNextScene = true;
	}
}
