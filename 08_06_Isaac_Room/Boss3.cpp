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
	Timer = 0;
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

	pattern1_Use = false;
	pat1_Timer = 0.5f;
	pat1_Time = 0.5f;
	pat1_Counter = 0;

	pattern2_Use = false;
	sum = 0;
	pat2_Timer = 0.5f;
	pat2_Time = 0.5f;
	pat2_Counter = 0;

	pattern3_Use = false;
	pat3_Timer = 0.5f;
	pat3_Time = 0.5f;
	pat3_Counter = 0;

	idleTimer = 0;
	idleTime = 1;
	idle_Attack_Time = 0.07f;
	idle_Attack_Timer = 0.07f;
	idle_Attack_Count = 0;
	isHited = false;
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

		if(phase != 3)
			PatternUse(deltaTime);

		if ((phase == 1 || phase == 2) && isHited && isCool)
			IdlePattern(deltaTime);
		else
		{
			if (!isCool)
			{
				idleTimer += deltaTime;
				if (idleTimer > idleTime)
				{
					isCool = true;
					idleTimer = 0;
				}
			}
		}

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
	
	isHited = true;

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

	if (transTimer > 0.4f && !pattern1_Use && !pattern2_Use && !pattern3_Use)
	{
		pos_x = 350 * cos(270 + pAngle * D3DX_PI / 180);
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
	if (bPattern)
	{
		bPattern = false;

		if (Timer > Time)
		{
			Time = 5;
			Timer = 0;

			switch (patternIndex)
			{
			case 0:
				pattern1_Use = true;
				break;
			case 1:
				pattern2_Use = true;
				break;
			case 2:
				pattern3_Use = true;
				break;
			case 3:
				pattern1_Use = true;
				break;
			}
		}
	}

	if (Timer > Time && !bPattern)
	{
		Timer = 0;
		bPattern = true;

		patternIndex = rand() % phase;

		switch (phase)
		{
		case 1:
			renderer->SetAni(1);
			Time = 0;
			break;
		case 2:
			renderer->SetAni(3);
			Time = 0;
			break;
		case 3:
			renderer->SetAni(5);
			Time = 0;
			break;
		case 4:
			renderer->SetAni(6);
			Time = 0;
			break;
		}
	}

	if(pattern1_Use)
		Pattern1(deltaTime);

	if(pattern2_Use)
		Pattern2(deltaTime);

	if (pattern3_Use)
		Pattern3(deltaTime);
}

void Boss3::Pattern1(float deltaTime)
{
	pat1_Timer += deltaTime;
	if (pat1_Timer > pat1_Time)
	{
		for (int i = 0; i < 5; ++i)
		{
			EnemyBullet * temp = new EnemyBullet;
			temp->position = position;
			temp->vMoveVector = g_pPlayer->position - position;

			D3DXMATRIX mtemp;
			D3DXMatrixRotationZ(&mtemp, D3DXToRadian(12 - 6 * i));
			D3DXVec2TransformNormal(&temp->vMoveVector, &temp->vMoveVector, &mtemp);
		}

		pat1_Counter++;
		pat1_Timer = 0;
		if (pat1_Counter >= 4)
		{
			pat1_Timer = 0.5f;
			pat1_Counter = 0;
			SetIdle();
			pattern1_Use = false;
		}
	}
}


void Boss3::Pattern2(float deltaTime)
{
	pat2_Timer += deltaTime;
	if (pat2_Timer > pat2_Time)
	{
		for (int i = 0; i <= 15; ++i)
		{
			EnemyBullet * temp = new EnemyBullet;
			temp->position = position;
			temp->vMoveVector = g_pPlayer->position - position;

			D3DXMATRIX mtemp;
			D3DXMatrixRotationZ(&mtemp, D3DXToRadian(i * 24));
			D3DXVec2TransformNormal(&temp->vMoveVector, &temp->vMoveVector, &mtemp);
			sum++;
		}

		pat2_Counter++;
		pat2_Timer = 0;
		if (pat2_Counter >= 4)
		{
			pat2_Timer = 0.5f;
			pat2_Counter = 0;
			SetIdle();
			pattern2_Use = false;
		}
	}
}

void Boss3::Pattern3(float deltaTime)
{
	pat3_Timer += deltaTime;
	if (pat3_Timer > pat3_Time)
	{
		for (int i = 0; i <= 12; ++i)
		{
			EnemyBullet * temp = new EnemyBullet(true);
			temp->position = position;
			temp->vMoveVector = g_pPlayer->position - position;

			D3DXMATRIX mtemp;
			D3DXMatrixRotationZ(&mtemp, D3DXToRadian(i * 30));
			D3DXVec2TransformNormal(&temp->vMoveVector, &temp->vMoveVector, &mtemp);
			sum++;
		}

		pat3_Counter++;
		pat3_Timer = 0;
		if (pat3_Counter >= 4)
		{
			pat3_Timer = 0.5f;
			pat3_Counter = 0;
			SetIdle();
			pattern3_Use = false;
		}
	}
}

void Boss3::IdlePattern(float deltaTime)
{
	idle_Attack_Timer += deltaTime;
	if (idle_Attack_Timer > idle_Attack_Time && isCool)
	{
		switch (phase)
		{
		case 1:
		{
			EnemyBullet * temp = new EnemyBullet;
			temp->position = position;
			temp->vMoveVector = g_pPlayer->position - position;
		}
		break;
		case 2:
		{
			ChaseBullet * temp = new ChaseBullet;
			temp->position = position;
			temp->vMoveVector = g_pPlayer->position - position;
		}
		break;
		}

		idle_Attack_Timer = 0;
		idle_Attack_Count++;

		if (idle_Attack_Count >= 3)
		{
			isCool = false;
			isHited = false;
			idleTimer = 0;
			idle_Attack_Timer = 0.07f;
			idle_Attack_Count = 0;
		}
	}
}

void Boss3::SetIdle()
{
	switch (phase)
	{
	case 1:
		renderer->SetAni(0);
		break;
	case 2:
		renderer->SetAni(2);
		break;
	case 4:
		renderer->SetAni(5);
		break;
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

