#include "DXUT.h"
#include "Boss2.h"


Boss2::Boss2()
{
}


Boss2::~Boss2()
{
}

void Boss2::Start()
{
	type = ENEMY_BOSS;

	// ��������Ʈ ������ �߰�
	renderer = new CSpriteRenderer(L"Boss2", L"Assets/Images/Boss/Boss2_", L"png", true, 4, 13, 0.075);
	renderer->SetIndex(0, 0, 5, true);
	renderer->SetIndex(1, 5, 5, false);
	renderer->SetIndex(2, 10, 2, false);
	renderer->SetIndex(3, 12, 1, false);

	fMoveSpeed = 100;

	bDie = false;
	maxHP = 250;
	hp = 250;
	bossHPBar = new HPBar;

	bPattern = false;
	Timer = 1;
	Time = 1;

	scale = { 2,2 };

	CreateCollider(CL_ENEMY, 30);
	SetCollision(CL_PLAYER_BULLET);

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
		g_OpenScene->ShakeCamera(1, 10);
	}

	if (bDie && Timer > Time)
	{
		bActive = false;
		bossHPBar->Emptybar->bActive = false;
		bossHPBar->bActive = false;
	}
}

void Boss2::OnCollision(CGameObject * CollisionObject)
{
	CollisionObject->bActive = false;
	hp -= bullet_damage;

	if (hp < 0)
	{
		bCollision = false;
	}
	else
	{
		colorTimer = 0;
		renderer->b = 50;
		renderer->g = 50;
	}
}

void Boss2::Move(float deltaTime)
{
	D3DXVec2Normalize(&vMoveVector, &vMoveVector);

	prevPos = position;
	position += vMoveVector * fMoveSpeed * deltaTime;

	if (position.x < g_OpenScene->limitrect.left + 50)
	{
		prevPos = position;
		vMoveVector.x = abs(vMoveVector.x);
	}
	else if (position.x > g_OpenScene->limitrect.right - 50)
	{
		prevPos = position;
		vMoveVector.x = -abs(vMoveVector.x);
	}
	else if (position.y < g_OpenScene->limitrect.top + 50)
	{
		prevPos = position;
		vMoveVector.y = abs(vMoveVector.y);
	}
	else if (position.y > g_OpenScene->limitrect.bottom - 50)
	{
		prevPos = position;
		vMoveVector.y = -abs(vMoveVector.y);
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
	if (!renderer->bAnimation)
	{
		bPattern = false;

		if (Timer > Time)
		{
			Time = 3;
			renderer->SetAni(0);
			Timer = 0;
			fMoveSpeed = 300;

			ChaseBall * temp1;
			EnemyHall * temp2;
			switch (patternIndex)
			{
			case 0:
				temp1 = new ChaseBall;
				temp1->position = position;
				break;
			case 1:
				temp2 = new EnemyHall;
				temp2->position = position;
				break;

			case 2:
				for (int i = 0; i < 20; ++i)
				{
					EnemyBullet * temp = new EnemyBullet;
					temp->position = position;
					temp->fMoveSpeed *= 1.2f - rand() % 41 * 0.01f; // 120 - 0 ~ 40 = 80 ~ 120
					temp->vMoveVector = g_pPlayer->position - position;

					int a = rand() % 31;

					D3DXMATRIX mtemp;
					D3DXMatrixRotationZ(&mtemp, D3DXToRadian(15 - a));
					D3DXVec2TransformNormal(&temp->vMoveVector, &temp->vMoveVector, &mtemp);
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
			Time = 0;
			break;

		case 1:
			renderer->SetAni(2);
			Time = 0;
			break;

		case 2:
			renderer->SetAni(1);
			Time = 0;
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
