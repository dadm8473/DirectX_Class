#include "DXUT.h"
#include "IsaacHead.h"


IsaacHead::IsaacHead()
{
}


IsaacHead::~IsaacHead()
{
}

void IsaacHead::Start()
{
	type = PLAYER_HEAD;
	// ��������Ʈ ������ �߰�
	renderer = new CSpriteRenderer(L"IsaacHead", L"Assets/Images/Isaac/Isaac_Head", L"png", true, 8, 8, 0.15);
	// �⺻ �ִϸ��̼�(��ݺ�, ��ҿ��� �̵����⿡ ����)
	renderer->SetIndex(0, 0, 1, false);
	renderer->SetIndex(2, 2, 1, false);
	renderer->SetIndex(4, 4, 1, false);
	renderer->SetIndex(6, 6, 1, false);

	// ���� �ִϸ��̼�(�ݺ�)
	renderer->SetIndex(1, 0, 2, true);
	renderer->SetIndex(3, 2, 2, true);
	renderer->SetIndex(5, 4, 2, true);
	renderer->SetIndex(7, 6, 2, true);

	scale = { 2, 2 };
	moveVector = { 0,0 };

	attackTime = 0.3;
	attackTimer = 0;
}
void IsaacHead::Update(float deltaTime)
{
	CGameObject::Update(deltaTime);
	
	attackTime = p_Attack_Speed;

	D3DXVECTOR2 vAttack(0, 0);

	if (g_Game.m_Input.KeyPress(VK_DOWN))
	{
		vAttack.y = -1;
		if (vAttack.y != prevAttack.y)
			renderer->SetAni(1);
	}
	else if (g_Game.m_Input.KeyPress(VK_UP))
	{
		vAttack.y = 1;
		if (vAttack.y != prevAttack.y)
			renderer->SetAni(5);
	}
	else if (g_Game.m_Input.KeyPress(VK_LEFT))
	{
		vAttack.x = -1;

		if (vAttack.x != prevAttack.x)
			renderer->SetAni(7);
	}
	else if (g_Game.m_Input.KeyPress(VK_RIGHT))
	{
		vAttack.x = 1;
		if (vAttack.x != prevAttack.x)
			renderer->SetAni(3);
	}

	attackTimer += deltaTime;

	if (vAttack.x == 0 && vAttack.y == 0)
		renderer->SetAni(moveDir);
	else if(attackTimer > attackTime)
	{
		attackTimer = 0;
		PlayerBullet * temp = new PlayerBullet;
		temp->position = position + vAttack * 10;
		temp->vMoveVector = vAttack + moveVector;
	}

	prevAttack = vAttack;
}