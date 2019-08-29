#include "DXUT.h"
#include "CEnemyAttackEffect.h"


CEnemyAttackEffect::CEnemyAttackEffect()
{
}


CEnemyAttackEffect::~CEnemyAttackEffect()
{
}

void CEnemyAttackEffect::Start()
{
	type = ENEMYEFFECT;

	if (!renderer)
		renderer = new CSpriteRenderer(L"EnemyAttack", L"Assets/Images/EnemyAttack/EnemyAttack_", L"png", true, 1, 4, 0.04);
	renderer->SetIndex(0, 0, 3, false);

	scale = { 3, 3 };

	bActive = false;
}

void CEnemyAttackEffect::Update(float deltaTime)
{
	CGameObject::Update(deltaTime);

	if (!renderer->bAnimation)
	{
		renderer->SetAni(0);
		bActive = false;
	}
}
