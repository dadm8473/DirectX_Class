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

	maxHP = 1000;
	hp = 1000;
	playerHPbar = new HPBar;

	maxMP = 50;
	mp = 50;
	playerMPbar = new HPBar;

	bDodge = false;
	dodgeTimer = 0;
	dodgeTime = 1;

	scale = { 0.3, 0.3 };

	position = { 100,100 };

	CreateCollider(CL_PLAYER, 10);
	SetCollision(CL_ENEMY_BULLET);
}

void CPlayer::Update(float deltaTime)
{
	deltaTime = g_Game.unscaleTime;

	CGameObject::Update(deltaTime);
	
	Move(deltaTime);

	HPControl(deltaTime);

	DodgeTime(deltaTime);

	if (0 < mp && g_Game.m_Input.KeyPress(VK_SPACE))
	{
		g_Game.timeScale = 0.5;
		mp -= 25 * deltaTime;
	}
	else
	{
		if (mp < maxMP)
		{
			mp += deltaTime * 5;
		}
		else
			mp = maxMP;
	}

	playerMPbar->position = position + D3DXVECTOR2(0, 30);
	playerMPbar->ratio = mp / maxMP;

	if (g_Game.m_Input.KeyUp(VK_SPACE))
		g_Game.timeScale = 1;
}

void CPlayer::OnCollision(CGameObject* CollisionObject)
{
	hp -= 25;
	bDodge = true;
	bCollision = false;

	g_OpenScene->ShakeCamera(1, 5);

	if (hp < 0)
	{
		char temp[100];
		memset(temp, 0, sizeof(temp));
		sprintf(temp, "GAME OVER. Score : %.2lf", g_Game.TimeScore);

		MessageBoxA(DXUTGetHWND(), temp, "TryWorld MSG Box", MB_OK);

		g_OpenScene->bNextScene = true;
		bActive = false;
	}
}

void CPlayer::Move(float deltaTime)
{
	D3DXVECTOR2 vMove(0, 0);

	if (g_Game.m_Input.KeyPress(VK_DOWN))
		vMove.y = -1;
	else if (g_Game.m_Input.KeyPress(VK_UP))
		vMove.y = 1;
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
	if (vMove.x == 0)
		renderer->SetAni(0);

	prevMoveX = vMove.x;

	D3DXVec2Normalize(&vMove, &vMove);

	prevPos = position;
	position += vMove * fMoveSpeed * deltaTime;

	if ((position.x < -512 || position.x > 512
		|| position.y < -384 || position.y > 384))
	{
		position = prevPos;
	}
}

void CPlayer::HPControl(float deltaTime)
{
	playerHPbar->position = position + D3DXVECTOR2(0, 60);
	playerHPbar->ratio = hp / maxHP;

	if (hp < maxHP)
	{
		hp += deltaTime * 0.5f;
	}
	else
		hp = maxHP;


}

void CPlayer::DodgeTime(float deltaTime)
{
	if (bDodge = true)
	{
		dodgeTimer += deltaTime;
		if (dodgeTimer > dodgeTime)
		{
			dodgeTimer = 0;
			bDodge = false;
			bCollision = true;
		}
	}
}
