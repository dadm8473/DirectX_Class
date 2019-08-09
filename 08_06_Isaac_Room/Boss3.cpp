#include "DXUT.h"
#include "Boss3.h"


Boss3::Boss3()
{
}


Boss3::~Boss3()
{
}

void Boss3::Start()
{
	type = ENEMY_BOSS;

	renderer = new CSpriteRenderer(L"Boss3", L"Assets/Images/Boss/Boss3_", L"png", true, 7, 20, 0.1);
	// 1 페이즈
	renderer->SetIndex(0, 0, 1, false);		// Idle
	renderer->SetIndex(1, 0, 4, true);		// Pattern
	// 2 페이즈
	renderer->SetIndex(2, 4, 1, false);		// Idle
	renderer->SetIndex(3, 4, 4, true);		// Pattern
	// 3 페이즈
	renderer->SetIndex(4, 8, 11, true);		// Transform
	renderer->SetIndex(5, 12, 7, true);		// Idle
	renderer->SetIndex(6, 19, 1, false);	// Pattern

	phase = 1;
	
	fMoveSpeed = 100;
	pAngle = 100;

	pos_x = 0;
	pos_y = 0;

	moveTime = 0.0005f;
	moveTimer = 0;

	transTime = 2.2f;
	transTimer = 0;

	bDie = false;
	maxHP = 1000;
	hp = 1000;
	bossHPBar = new HPBar;

	bPattern = false;
	Timer = 1;
	Time = 1;

	scale = { 2,2 };

	CreateCollider(CL_ENEMY, 20);
	SetCollision(CL_PLAYER_BULLET);

	vMoveVector = { -1, 1 };
	D3DXVec2Normalize(&vMoveVector, &vMoveVector);

	colorTimer = 0;
	colorTime = 0.2;

	pos_x = 320 * cos(270 + pAngle * D3DX_PI / 180);
	pos_y = 230 * sin(270 + pAngle * D3DX_PI / 180);
}

void Boss3::Update(float deltaTime)
{
	CGameObject::Update(deltaTime);
	HPControl(deltaTime);
	Timer += deltaTime;
	
	if (hp > 0)
	{
		if (phase == 4)
		{
			moveTimer += deltaTime;
			if (moveTimer > moveTime)
			{
				Move(deltaTime);
				moveTimer = 0;
			}
		}
		PatternUse(deltaTime);
		HitColorSet(deltaTime);
		PhaseControl(deltaTime);
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

void Boss3::OnCollision(CGameObject * CollisionObject)
{
	CollisionObject->bActive = false;
	if(phase != 3)
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

void Boss3::Move(float deltaTime)
{
	/*D3DXVec2Normalize(&vMoveVector, &vMoveVector);

	prevPos = position;
	position += vMoveVector * fMoveSpeed * deltaTime;*/

	/*x_cos = (cos(pAngle) * 5);
	y_sin = (sin(pAngle) * 5);

	pos_x = x_cos - y_sin;
	pos_y = x_cos + y_sin;

	pAngle += 5;*/

	if (transTimer > 0.4f)
	{
		pos_x = 320 * cos(270 + pAngle * D3DX_PI / 180);
		pos_y = 230 * sin(270 + pAngle * D3DX_PI / 180);

		pAngle += 1.5f;

		position = D3DXVECTOR2(pos_x, pos_y + 30);

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
	else
	{
		D3DXVec2Lerp(&position, &position, &D3DXVECTOR2(pos_x, pos_y + 30), 0.1);
		transTimer += deltaTime;
	}
}

void Boss3::HPControl(float deltaTime)
{
	bossHPBar->position = position + D3DXVECTOR2(0, -50);
	bossHPBar->ratio = hp / maxHP;

	if (hp < maxHP)
	{
		hp += deltaTime * 0.5f;
	}
	else
		hp = maxHP;
}

void Boss3::PhaseControl(float deltaTime)
{
	if (phase == 1 && hp < maxHP * 0.7f)
	{
		renderer->SetAni(2);
		phase = 2;
	}
	else if (phase == 2 && hp < maxHP * 0.4f)
	{
		renderer->SetAni(4);
		phase = 3;
		renderer->delay = 0.2f;
	}
	else if (phase == 3)
	{
		transTimer += deltaTime;
		if (transTime < transTimer)
		{
			renderer->SetAni(5);
			phase = 4;
			renderer->delay = 0.07f;
			transTimer = 0;
		}

		if (hp < maxHP)
			hp += 500 * deltaTime;
		else
			hp = maxHP;
	}
}

void Boss3::PatternUse(float deltaTime)
{
	if (!renderer->bAnimation)
	{
		bPattern = false;

		if (Timer > Time)
		{
			Time = 3;
			Timer = 0;

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
			//renderer->SetAni(1);
			Time = 0;
			break;

		case 1:
			//renderer->SetAni(2);
			Time = 0;
			break;

		case 2:
			//renderer->SetAni(1);
			Time = 0;
			break;

		default:
			break;
		}
	}

}

void Boss3::HitColorSet(float deltaTime)
{
	if (colorTimer > colorTime)
	{
		renderer->b = 255;
		renderer->g = 255;
	}
	else
		colorTimer += deltaTime;
}

