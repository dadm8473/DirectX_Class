#include "DXUT.h"
#include "Boss2.h"
#include <time.h>

void Boss2::Start()
{
	type = ENEMY_BOSS;

	// 스프라이트 렌더러 추가
	renderer = new CSpriteRenderer(L"Boss2", L"Assets/Images/Boss/Boss2_", L"png", true, 4, 13, 0.05);
	renderer->SetIndex(0, 0, 5, true);
	renderer->SetIndex(1, 5, 5, true);
	renderer->SetIndex(2, 0, 12, true);
	renderer->SetIndex(3, 12, 1, false);

	fMoveSpeed = 100;

	bDie = false;
	maxHP = 2500;
	hp = 2500;
	bossHPBar = new HPBar;

	bPattern = false;
	Timer = 1;
	Time = 1;

	isAttack = false;

	position = { 0, 250 };
	scale = { 2,2 };

	CreateCollider(CL_ENEMY, 50);
	SetCollision(CL_PLAYER_BULLET);

	bCollision = true;

	vMoveVector = { -1, 1 };
	D3DXVec2Normalize(&vMoveVector, &vMoveVector);

	colorTimer = 0;
	colorTime = 0.2;
}

void Boss2::Update(float deltaTime)
{
	CGameObject::Update(deltaTime);
	HPControl(deltaTime);
	Timer += deltaTime;

	if (hp > 0)
	{
		Move(deltaTime);
		PatternUse(deltaTime);
		HitColorSet(deltaTime);
	}
	else if (!bDie)
	{
		bDie = true;
		renderer->SetAni(3);
		Timer = 0;
		Time = 1;
		g_OpenScene->CameraShake(1, 10);
	}

	if (bDie && Timer > Time)
	{
		char temp[100];
		memset(temp, 0, sizeof(temp));
		sprintf(temp, "GAME CLEAR. CLEAR TIME : %.2lf", g_Game.TimeScore);

		MessageBoxA(DXUTGetHWND(), temp, "TryWorld MSG Box", MB_OK);

		g_OpenScene->bNextScene = true;
		bActive = false;
	}
}

void Boss2::OnCollision(CGameObject * CollisionObject)
{
	CollisionObject->bActive = false;
	hp -= 5;

	if (hp < 0)
	{
		bCollision = false;
	}
	else
	{
		colorTimer = 0;
		renderer->b = 100;
		renderer->g = 100;
	}
}

void Boss2::Move(float deltaTime)
{
	D3DXVec2Normalize(&vMoveVector, &vMoveVector);

	prevPos = position;
	position += vMoveVector * fMoveSpeed * deltaTime;

	if (position.x < -512 + 50 || position.x > 512 - 50)
	{
		prevPos = position;
		vMoveVector.x *= -1;
	}
	else if (position.y < -384 + 50 || position.y > 384 - 50)
	{
		vMoveVector.y *= -1;
		prevPos = position;
	}
}

void Boss2::HPControl(float deltaTime)
{
	bossHPBar->position = position + D3DXVECTOR2(0, -100);
	bossHPBar->ratio = hp / maxHP;

	if (hp < maxHP)
	{
		hp += deltaTime * 0.5f;
	}
	else
		hp = maxHP;
}

void Boss2::PatternUse(float deltaTime)
{
	if (isAttack)
	{
		bPattern = false;

		if (Timer > Time)
		{
			Time = 3;
			renderer->SetAni(0);
			Timer = 0;
			isAttack = false;
			fMoveSpeed = 300;

			switch (patternIndex)
			{
			case 0:
			{
				ChaseEnemy* temp = new ChaseEnemy(1);
				temp->position = position;
			}
				break;

			case 1:
			{
				ChaseEnemy* temp = new ChaseEnemy(2);
				temp->position = position;
			}
				break;

			case 2:
				for (int i = 0; i < 11; ++i)
				{
					EnemyBullet * temp = new EnemyBullet;
					temp->position = position;
					temp->vMoveVector = g_pPlayer->position - position;

					D3DXMATRIX mtemp;
					int randSum = rand() % 6 + 1;
					D3DXMatrixRotationZ(&mtemp, D3DXToRadian(30 - randSum * i));
					D3DXVec2TransformNormal(&temp->vMoveVector, &temp->vMoveVector, &mtemp);

					temp->fMoveSpeed = 200 + (randSum * 30);
				}
				break;
			}
		}
	}

	if (Timer > Time && !bPattern)
	{
		Timer = 0;
		bPattern = true;
		patternIndex = rand() % 3;

		switch (patternIndex)
		{
		case 0:
			renderer->SetAni(1);
			isAttack = true;
			Time = 0.2;
			break;

		case 1:
			renderer->SetAni(2);
			isAttack = true;
			Time = 0.2;
			break;

		case 2:
			renderer->SetAni(1);
			isAttack = true;
			Time = 0.2;
			break;

		default:
			break;
		}
	}
}

void Boss2::HitColorSet(float deltaTime)
{
	if (colorTimer > colorTime)
	{
		renderer->b = 255;
		renderer->g = 255;
	}
	else
		colorTimer += deltaTime;
}
