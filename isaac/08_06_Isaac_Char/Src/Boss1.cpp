#include "DXUT.h"
#include "Boss1.h"


Boss1::Boss1()
{
}


Boss1::~Boss1()
{
}

void Boss1::Start()
{
	type = ENEMY_BOSS;

	// 스프라이트 렌더러 추가
	renderer = new CSpriteRenderer(L"Boss", L"Assets/Images/Boss/Boss1_", L"png", true, 7, 25, 0.05);
	renderer->SetIndex(0, 0, 1, false);
	renderer->SetIndex(1, 0, 5, false);
	renderer->SetIndex(2, 14, 9, false);
	renderer->SetIndex(3, 5, 2, true);
	renderer->SetIndex(4, 5, 6, false);
	renderer->SetIndex(5, 11, 3, false);
	renderer->SetIndex(6, 23, 2, true);

	renderer->a = 180;

	fMoveSpeed = 100;

	bDie = false;
	maxHP = 250;
	hp = 250;
	bossHPBar = new HPBar;

	bPattern = false;
	Timer = 1;
	Time = 1;

	position = { 0, 250 };
	scale = { 2,2 };

	CreateCollider(CL_ENEMY, 50);
	SetCollision(CL_PLAYER_BULLET);

	bCollision = false;

	vMoveVector = { -1, 1 };
	D3DXVec2Normalize(&vMoveVector, &vMoveVector);

	for (int i = 0; i < 3; ++i)
	{
		chaseAddon[i] = new ChaseEnemy;
	}
	chaseAddon[0]->position = position + D3DXVECTOR2(-70, -40);
	chaseAddon[1]->position = position + D3DXVECTOR2(70, -40);
	chaseAddon[2]->position = position + D3DXVECTOR2(0, 100);

	colorTimer = 0;
	colorTime = 0.2;
}

void Boss1::Update(float deltaTime)
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
		renderer->SetAni(6);
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

void Boss1::OnCollision(CGameObject * CollisionObject)
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

void Boss1::Move(float deltaTime)
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

void Boss1::HPControl(float deltaTime)
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

void Boss1::PatternUse(float deltaTime)
{
	if (!bCollision)
	{
		for (int i = 0; i < 3 && !bPattern; ++i)
		{
			if (chaseAddon[i]->bActive)
				return;

			if (i == 2)
			{
				bPattern = true;
				renderer->SetAni(1);
				g_OpenScene->CameraShake(0.5, 10);
			}
		}

		vMoveVector = { 0, 1 };
		fMoveSpeed = 600;

		if (position.y > 300)
		{
			position.y = 300;
			vMoveVector.y = 0;
			if (!renderer->bAnimation)
			{
				renderer->SetAni(2);
				bCollision = true;
				vMoveVector = { 1, 0 };
				fMoveSpeed = 300;
				renderer->a = 255;
				Time = 4;
			}
		}
		return;
	}

	if (!renderer->bAnimation)
	{
		bPattern = false;

		if (Timer > Time)
		{
			Time = 3;
			renderer->SetAni(3);
			Timer = 0;
			fMoveSpeed = 300;


			switch(patternIndex)
			{
			case 1:
				for (int i = 0; i < 11; ++i)
				{
					EnemyBullet * temp = new EnemyBullet;
					temp->position = position;
					temp->vMoveVector = g_pPlayer->position - position;

					D3DXMATRIX mtemp;
					D3DXMatrixRotationZ(&mtemp, D3DXToRadian(30 - 6 * i));
					D3DXVec2TransformNormal(&temp->vMoveVector, &temp->vMoveVector, &mtemp);
				}
				break;

			case 2:
				for (int i = 0; i < 2; ++i)
				{
					chaseAddon[i] = new ChaseEnemy;
				}
				chaseAddon[0]->position = position + D3DXVECTOR2(-70, -20);
				chaseAddon[1]->position = position + D3DXVECTOR2(70, -20);
				break;
			}
		}
	}

	if (Timer > Time && !bPattern)
	{
		Timer = 0;
		patternIndex = rand() % 3;

		switch (patternIndex)
		{
		case 0:
			if (g_pPlayer->position.y > 250)
			{
				renderer->SetAni(4);
				fMoveSpeed = 800;
				Time = 2;
			}
			else
				Time = 0;
			break;

		case 1:
			renderer->SetAni(5);
			Time = 0.5;
			break;

		case 2:
			renderer->SetAni(5);
			Time = 0.5;
			break;

		default:
			break;
		}
	}

}

void Boss1::HitColorSet(float deltaTime)
{
	if (colorTimer > colorTime)
	{
		renderer->b = 255;
		renderer->g = 255;
	}
	else
		colorTimer += deltaTime;
}
