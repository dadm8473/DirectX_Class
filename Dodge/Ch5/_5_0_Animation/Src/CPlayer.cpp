#include "DXUT.h"
#include "CPlayer.h"

void CPlayer::Start()
{	
	// 스프라이트 렌더러 추가
	renderer = new CSpriteRenderer(L"Player",L"Assets/Images/Player/player000", L"png", true, 3, 40, 0.05);
	renderer->SetIndex(0, 0, 1, false);
	renderer->SetIndex(1, 0, 10, false);
	renderer->SetIndex(2, 20, 10, false);

	fMoveSpeed = 400;

	position = { 512,384 };
	scale = { 0.5f, 0.5f };

	CreateCollider(CL_PLAYER, 10);
	SetCollision(CL_BULLET);
}

void CPlayer::Update(float deltaTime)
{
	CGameObject::Update(deltaTime);

	D3DXVECTOR2 vMove(0, 0);

	if (g_Game.m_Input.KeyPress(VK_DOWN))
		vMove.y = 1;
	else if (g_Game.m_Input.KeyPress(VK_UP))
		vMove.y = -1;
	if (g_Game.m_Input.KeyPress(VK_LEFT))
	{
		vMove.x = -1;
		if (vMove.x * prevMoveX <= 0)
			renderer->SetAni(2);
	}
	else if (g_Game.m_Input.KeyPress(VK_RIGHT))
	{
		vMove.x = 1;
		if (vMove.x * prevMoveX <= 0)
			renderer->SetAni(1);
	}
	if(vMove.x == 0)
		renderer->SetAni(0);

	prevMoveX = vMove.x;

	D3DXVec2Normalize(&vMove, &vMove);

	prevPos = position;
	position += vMove * fMoveSpeed * deltaTime;

	if ((position.x < 0 || position.x > 1024
		|| position.y < 0 || position.y > 768))
	{
		position = prevPos;
	}
}

void CPlayer::OnCollision(CGameObject* CollisionObject)
{
	char temp[100];
	memset(temp, 0, sizeof(temp));

	sprintf(temp, "GAME OVER. Score : %.2lf", g_Game.TimeScore);

	MessageBoxA(DXUTGetHWND(), temp, "TryWorld MSG Box", MB_OK);
	g_OpenScene->bNextScene = true;	
	bActive = false;

	g_pPlayer = NULL;
}
