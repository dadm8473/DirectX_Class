#include "DXUT.h"
#include "CScarecrow.h"


CScarecrow::CScarecrow()
{
}


CScarecrow::~CScarecrow()
{
}

void CScarecrow::Start()
{
	type = ENEMY;

	if (!renderer)
		renderer = new CSpriteRenderer(L"Scarecrow", L"Assets/Images/ScareCrow", L"png", false);

	renderer->rect = new RECT;
	SetRect(renderer->rect, 0, 0, renderer->GetTextureInfo().Width, renderer->GetTextureInfo().Height);

	CreateRigidBody(D3DXVECTOR2(0, 15), D3DXVECTOR2(30, 30));

	CreateCollider(CL_ENEMY, D3DXVECTOR2(0, 15), D3DXVECTOR2(30, 30));
	SetCollision(CL_PLAYERATTACK);

	scale = { 1,1 };

	pivot.y = 0;
}

void CScarecrow::Update(float deltaTime)
{
	CGameObject::Update(deltaTime);

	if (g_Game.Input.KeyDown(VK_F1))
	{
		velocity = { 0,0 };
		position = { 0,0 };
	}

}
