#include "DXUT.h"
#include "StartButton.h"


StartButton::StartButton()
{
}


StartButton::~StartButton()
{
}

void StartButton::Start()
{
	type = HUD;
	renderer = new CSpriteRenderer(L"StartButton", L"Assets/Images/UI/Start", L"png", false);

	CreateCollider(CL_UI, 70);
	SetCollision(CL_MOUSE);
}

void StartButton::OnCollision(CGameObject * CollisionObject)
{
	g_OpenScene->bNextScene = true;
}
