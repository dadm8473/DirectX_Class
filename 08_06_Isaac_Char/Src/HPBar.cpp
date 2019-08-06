#include "DXUT.h"
#include "HPBar.h"


void HPBar::Start()
{
	type = HUD;
	renderer = new CSpriteRenderer(L"HPBar", L"Assets/Images/UI/HPBar", L"png", false);
	renderer->rect = new RECT;
	renderer->a = 125;

	Emptybar = new CGameObject(L"EmptyBar", L"Assets/Images/UI/EmptyBar", L"png", false);
	Emptybar->type = HUD;
	Emptybar->renderer->a = 125;
}

void HPBar::Update(float deltaTime)
{
	CGameObject::Update(deltaTime);

	SetRect(renderer->rect,0, 0, renderer->GetTextureInfo().Width * ratio, renderer->GetTextureInfo().Height);
	Emptybar->position = position;
	//Emptybar->Update(deltaTime);
}
