#include "DXUT.h"
#include "Isaac.h"


Isaac::Isaac()
{
}


Isaac::~Isaac()
{
}

void Isaac::Start()
{
	type = PLAYER;
	// 스프라이트 렌더러 추가
	renderer = new CSpriteRenderer(L"Isaac", L"Assets/Images/Isaac/Isaac_Body", L"png", true, 3, 20, 0.05);
	renderer->SetIndex(0, 0, 1, false);
	renderer->SetIndex(1, 0, 10, true);
	renderer->SetIndex(2, 10, 10, true);

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

	scale = { 2, 2 };

	position = { 0, -100};

	CreateCollider(CL_PLAYER, 10);
	SetCollision(CL_ENEMY_BULLET);
	SetCollision(CL_ENEMY);

	head = new IsaacHead;
}

void Isaac::Update(float deltaTime)
{
	deltaTime = g_Game.unscaleTime;
	
	if (head)
	{
		head->position = position + D3DXVECTOR2(0, 14 * scale.y);
		head->moveVector = prevMove * 0.5f;
	}

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

	playerMPbar->position = position + D3DXVECTOR2(0, 75);
	playerMPbar->ratio = mp / maxMP;

	if (g_Game.m_Input.KeyUp(VK_SPACE))
		g_Game.timeScale = 1;
}

void Isaac::OnCollision(CGameObject* CollisionObject)
{
	hp -= 25;
	bDodge = true;
	bCollision = false;

	g_OpenScene->ShakeCamera(1, 5);

	if (hp < 0)
	{
		char temp[100];
		memset(temp, 0, sizeof(temp));
		sprintf(temp, "GAME OVER. CLEAR TIME : %.2lf", g_Game.TimeScore);

		MessageBoxA(DXUTGetHWND(), temp, "TryWorld MSG Box", MB_OK);

		g_OpenScene->bNextScene = true;
		bActive = false;
	}
}

void Isaac::Move(float deltaTime)
{
	D3DXVECTOR2 vMove(0, 0);

	if (g_Game.m_Input.KeyPress('S'))
	{
		vMove.y = -1;
		if (vMove.y != prevMove.y)
		{
			renderer->SetAni(1);
			head->moveDir = 0;
		}
	}
	else if (g_Game.m_Input.KeyPress('W'))
	{
		vMove.y = 1;
		if (vMove.y != prevMove.y)
		{
			renderer->SetAni(1);
			head->moveDir = 4;
		}
	}
	if (g_Game.m_Input.KeyPress('A'))
	{
		vMove.x = -1;

		if (vMove.x != prevMove.x)
		{
			renderer->SetAni(2);
			scale.x = -2;
			head->moveDir = 6;
		}
	}
	else if (g_Game.m_Input.KeyPress('D'))
	{
		vMove.x = 1;
		if (vMove.x != prevMove.x)
		{
			renderer->SetAni(2);
			scale.x = 2;
			head->moveDir = 2;
		}
	}

	if (vMove.x == 0 && vMove.y == 0)
		renderer->SetAni(0);

	prevMove = vMove;

	D3DXVec2Normalize(&vMove, &vMove);

	prevPos = position;
	position += vMove * fMoveSpeed * deltaTime;

	if (position.x < g_OpenScene->limitrect.left + 50 || position.x >g_OpenScene->limitrect.right - 50)
		position.x = prevPos.x;
	if(position.y < g_OpenScene->limitrect.top + 50 || position.y > g_OpenScene->limitrect.bottom - 50)
		position.y = prevPos.y;
}

void Isaac::HPControl(float deltaTime)
{
	playerHPbar->position = position + D3DXVECTOR2(0, 100);
	playerHPbar->ratio = hp / maxHP;

	if (hp < maxHP)
	{
		hp += deltaTime * 0.5f;
	}
	else
		hp = maxHP;


}

void Isaac::DodgeTime(float deltaTime)
{
	if (bDodge)
	{
		renderer->a = 170;
		
		if(head->renderer)
			head->renderer->a = 170;

		dodgeTimer += deltaTime;
		if (dodgeTimer > dodgeTime)
		{
			dodgeTimer = 0;
			bDodge = false;
			bCollision = true;

			renderer->a = 255;
			head->renderer->a = 255;
		}
	}
}
