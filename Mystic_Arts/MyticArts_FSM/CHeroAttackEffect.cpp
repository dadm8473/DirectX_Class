#include "DXUT.h"
#include "CHeroAttackEffect.h"


CHeroAttackEffect::CHeroAttackEffect()
{
}


CHeroAttackEffect::~CHeroAttackEffect()
{
}

void CHeroAttackEffect::Start()
{
	type = PLAYEREFFECT;

	if (!renderer)
		renderer = new CSpriteRenderer(L"HeroAttack", L"Assets/Images/Effect/HeroAttack_", L"png", true, 1, 4, 0.04);
	renderer->SetIndex(0, 0, 3, false);

	bActive = false;
}

void CHeroAttackEffect::Update(float deltaTime)
{
	CGameObject::Update(deltaTime);

	if (!renderer->bAnimation)
	{
		renderer->SetAni(0);
		bActive = false;
	}
}
