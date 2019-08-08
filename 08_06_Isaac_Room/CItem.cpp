#include "DXUT.h"
#include "CItem.h"

CItem::CItem(int type)
	: type(type)
{
}


CItem::~CItem()
{
}

void CItem::Start()
{
	// 스프라이트 렌더러 추가
	switch (type)
	{
	case 1:
		renderer = new CSpriteRenderer(L"Item1", L"Assets/Images/Item/DamageItem", L"png", false);
		break;
	case 2:
		renderer = new CSpriteRenderer(L"Item2", L"Assets/Images/Item/AttackSpeedItem", L"png", false);
		break;
	}

	CreateCollider(CL_ITEM, 10);
	SetCollision(CL_PLAYER);
}

void CItem::Update(float deltaTime)
{
	CGameObject::Update(deltaTime);
}

void CItem::OnCollision(CGameObject * CollisionObject)
{
	switch (type)
	{
	case 1:
		bullet_damage += 100;
		break;
	case 2:
		p_Attack_Speed = 0.02f;
		break;
	}

	bActive = false;
}