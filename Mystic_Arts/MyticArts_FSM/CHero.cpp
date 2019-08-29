#include "DXUT.h"
#include "CHero.h"

HeroIdle * HeroIdle::instance = new HeroIdle;
HeroMove * HeroMove::instance = new HeroMove;
HeroJump * HeroJump::instance = new HeroJump;
HeroFall * HeroFall::instance = new HeroFall;
HeroInAir * HeroInAir::instance = new HeroInAir;
HeroAttack * HeroAttack::instance = new HeroAttack;
HeroSkyAttack * HeroSkyAttack::instance = new HeroSkyAttack;
HeroSpecailAttack * HeroSpecailAttack::instance = new HeroSpecailAttack;
HeroGuard * HeroGuard::instance = new HeroGuard;

CHero::CHero()
{
}


CHero::~CHero()
{
}

void CHero::Start()
{
	type = PLAYER;

	if (!renderer)
		renderer = new CSpriteRenderer(L"Hero", L"Assets/Images/Player/Hero_", L"png", true, 25, 82, 0.06);

	renderer->SetIndex(0, 0, 7, true);			// 0 :  0,4  - idle
	renderer->SetIndex(1, 8, 12, false);		// 1 :  5,9  - move start
	renderer->SetIndex(2, 13, 17, true);		// 2 : 10,14 - move

	renderer->SetIndex(3, 18, 20, true);		// 3 : 15,17 - jump
	renderer->SetIndex(4, 21, 22, true);		// 4 : 18,19 - jump to fall

	renderer->SetIndex(5, 23, 24, true);		// 5 : 20,21 - fall
	renderer->SetIndex(6, 25, 25, false);		// 6 : 22,22 - fall attack

	renderer->SetIndex(7, 42, 43, false);		// 7 : 42,43 - attack 1
	renderer->SetIndex(8, 44, 46, false);		// 8 : 44,46 - attack 2
	renderer->SetIndex(9, 47, 53, false);		// 9 : 47,53 - attack 3
	renderer->SetIndex(10, 54, 57, false);		//10 : 54,57 - attack 4(돌려차기)
	renderer->SetIndex(11, 58, 62, false);		//11 : 58,62 - attack 5(다리후리기)
	renderer->SetIndex(12, 63, 66, false);		//12 : 63,66 - attack 6(올려차기)
	renderer->SetIndex(13, 63, 67, false);		//13 : 63,67 - attack 7(올려차 내려찍기)

	renderer->SetIndex(14, 68, 69, true);		//14 : 67,68 - attack 8 dash
	renderer->SetIndex(15, 70, 73, false);		//15 : 67,68 - attack 8(장풍)
	renderer->SetIndex(16, 75, 81, false);		//16 : 74,80 - attack 9(밀쳐내기)

	renderer->SetIndex(17, 26, 28, false);		//17 : 26,28 - jump attack 1
	renderer->SetIndex(18, 29, 32, false);		//18 : 29,32 - jump attack 2(돌려차기)
	renderer->SetIndex(19, 33, 36, false);		//19 : 33,36 - jump attack 3(내려찍기)

	renderer->SetIndex(20, 74, 74, false);		//20 : 74,74 - guard

	HeroIdle::instance->EnterState(this);

	heroAttackCollider = new CHeroAttackCollider;
	heroAttackCollider->parent = this;

	CreateRigidBody(D3DXVECTOR2(0, 20), D3DXVECTOR2(20, 60));

	CreateCollider(CL_PLAYER, D3DXVECTOR2(0, 30), D3DXVECTOR2(30, 60));
	SetCollision(CL_ENEMYATTACK);

	pivot.y = 0;

	moveSpeed = 300;
}

void CHero::Update(float deltaTime)
{
	CGameObject::Update(deltaTime);

	inputTimer += g_Game.unscaleTime;
	for (int i = 0; i < 4; ++i)
	{
		if (g_Game.Input.KeyDown(VK_LEFT + i))
		{
			inputTimer = 0;
			prevInput = nowInput;
			nowInput = i;
		}
	}

	if (inputTimer > 0.3)
	{
		prevInput = -1;
		nowInput = -1;
	}

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
	velocity.x = vMove.x * moveSpeed;

	if (position.x < g_OpenScene->limitrect.left + 20 || position.x >g_OpenScene->limitrect.right - 20)
		position.x = prevPos.x;

	return true;
}

int CHero::SetSpecialIndex()
{
	specialIndex = -1;
	switch (prevInput)
	{
	case LEFT: case RIGHT:
		if (nowInput == prevInput)
		{
			specialIndex = 0;
		}
		else if (nowInput == LEFT || nowInput == RIGHT)
		{
			specialIndex = 4;
		}
		break;
	case DOWN:
		if (nowInput == prevInput)
		{
			specialIndex = 6;
		}
		else if (nowInput == LEFT || nowInput == RIGHT)
		{
			specialIndex = 3;
		}
		break;
	case UP:
		if (nowInput == prevInput)
		{
			specialIndex = 2;
		}
		break;
	default:
		break;
	}

	return specialIndex;
}