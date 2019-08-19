#include "DXUT.h"
#include "CHero.h"

HeroIdle * HeroIdle::instance = new HeroIdle;
HeroMove * HeroMove::instance = new HeroMove;
HeroJump * HeroJump::instance = new HeroJump;
HeroFall * HeroFall::instance = new HeroFall;
HeroInAir * HeroInAir::instance = new HeroInAir;
HeroAttack * HeroAttack::instance = new HeroAttack;
HeroSpecailAttack * HeroSpecailAttack::instance = new HeroSpecailAttack;

CHero::CHero()
{
}


CHero::~CHero()
{
}

void CHero::Start()
{
	if (!renderer)
		renderer = new CSpriteRenderer(L"Hero", L"Assets/Images/Player/Hero_", L"png", true, 20, 81, 0.06);

	renderer->SetIndex(0, 0, 7, true);			// 0 :  0,4 - idle
	renderer->SetIndex(1, 8, 12, false);		// 1 :  5,9 - move start
	renderer->SetIndex(2, 13, 17, true);		// 2 : 10,14 - move
	renderer->SetIndex(3, 18, 20, true);		// 3 : 15,17 - jump
	renderer->SetIndex(4, 21, 22, true);		// 4 : 18,19 - jump to fall
	renderer->SetIndex(5, 23, 24, true);		// 5 : 20,21 - fall
	renderer->SetIndex(6, 25, 25, false);		// 6 : 22,22 - fall attack
	renderer->SetIndex(7, 42, 43, false);		// 7 : 42,43 - attack 1
	renderer->SetIndex(8, 44, 46, false);		// 8 : 44,46 - attack 2
	renderer->SetIndex(9, 47, 51, false);		// 9 : 47,51 - attack 3
	renderer->SetIndex(10, 52, 57, false);		//10 : 52,57 - attack 4
	renderer->SetIndex(11, 58, 62, false);		//11 : 18,62 - attack 5
	renderer->SetIndex(12, 63, 66, false);		//12 : 63,66 - attack 6

	HeroIdle::instance->EnterState(this);

	CreateRigidBody(D3DXVECTOR2(0, 20), D3DXVECTOR2(20, 60));

	pivot.y = 0;

	moveSpeed = 300;
}

void CHero::Update(float deltaTime)
{
	CGameObject::Update(deltaTime);
	
	if (nowState)
		nowState->UpdateState(this, deltaTime);
}

bool CHero::Move(float deltaTime)
{
	D3DXVECTOR2 vMove(0, 0);
	int aniIndex = 0;

	if (g_Game.Input.KeyPress(VK_LEFT))
	{
		vMove.x = -1;
	}
	else if (g_Game.Input.KeyPress(VK_RIGHT))
	{
		vMove.x = 1;
	}
	else
		return false;

	if (!bFlip && prevMove.x * vMove.x < 0)
	{
		scale.x = prevMove.x;
		vMove.x = 0;
	}
	else
	{
		prevMove = vMove;
	}

	scale.x = prevMove.x;

	D3DXVec2Normalize(&vMove, &vMove);

	prevPos = position;
	position += vMove * moveSpeed * deltaTime;

	if (position.x < g_OpenScene->limitrect.left + 20 || position.x >g_OpenScene->limitrect.right - 20)
		position.x = prevPos.x;
}