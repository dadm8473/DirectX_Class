#include "DXUT.h"
#include "Room.h"


Room::Room()
{
}


Room::~Room()
{
}

void Room::Start()
{
	type = BG_ROOM;
	// 스프라이트 렌더러 추가
	renderer = new CSpriteRenderer(L"Basement", L"Assets/Images/BG/BG", L"png", false);

	rect = {
		LONG(position.x - g_Game.windowWidth * 0.5),
		LONG(position.y - g_Game.windowHeight * 0.5),
		LONG(position.x + g_Game.windowWidth * 0.5),
		LONG(position.y + g_Game.windowHeight * 0.5),
	};

	for (int i = 0; i < 4; ++i)
	{
		door[i] = new Door;
		door[i]->bActive = false;
	}
	door[DOWN]->position = position + D3DXVECTOR2(0, -384);
	door[DOWN]->dir = DOWN;
	door[RIGHT]->position = position + D3DXVECTOR2(512, 0);
	door[RIGHT]->dir = RIGHT;							   
	door[UP]->position = position + D3DXVECTOR2(0, 384);
	door[UP]->dir = UP;									   
	door[LEFT]->position = position + D3DXVECTOR2(-512, 0);
	door[LEFT]->dir = LEFT;

	for each (CGameObject * var in enemyList)
	{
		var->position += position;
	}

	for each (CGameObject * var in itemList)
	{
		var->position += position;
	}

	bOpen = false;
	CheckPlayer();

	CreateCollider(CL_ROOM, 512);
	SetCollision(CL_ROOM);
}

void Room::Update(float deltaTime)
{
	CGameObject::Update(deltaTime);

	for each (CGameObject* var in enemyList)
	{
		if (var->bActive)
			return;
	}

	if (bOpen)
		for (int i = 0; i < 4; ++i)
		{
			if (door[i]->bStart)
			{
				door[i]->renderer->SetAni(1);
				door[i]->bCollision = true;
			}
		}
}

void Room::OnCollision(CGameObject * CollisionObject)
{
	D3DXVECTOR2 vDir = CollisionObject->position - position;

	if (vDir.x * vDir.y != 0)
		return;

	if (vDir.x > 0)
	{
		door[RIGHT]->bActive = true;
		door[RIGHT]->nextRoom = CollisionObject->position;
	}
	else if (vDir.x < 0)
	{
		door[LEFT]->bActive = true;
		door[LEFT]->nextRoom = CollisionObject->position;
	}
	else if (vDir.y > 0)
	{
		door[UP]->bActive = true;
		door[UP]->nextRoom = CollisionObject->position;
	}
	else if (vDir.y < 0)
	{
		door[DOWN]->bActive = true;
		door[DOWN]->nextRoom = CollisionObject->position;
	}
}

void Room::SetEnemy(CGameObject * enemy, D3DXVECTOR2 enemeyPos)
{
	enemy->bActive = false;
	enemy->position = enemeyPos;
	enemyList.push_back(enemy);
}

void Room::SetItem(CGameObject * item, D3DXVECTOR2 itemPos)
{
	item->bActive = false;
	item->position = itemPos;
	itemList.push_back(item);
}

void Room::CheckPlayer()
{
	POINT point = { g_pPlayer->position.x, g_pPlayer->position.y };

	if (!PtInRect(&rect, point))
	{
		bOpen = false;
		for (int i = 0; i < 4; ++i)
			door[i]->bCollision = false;
	}
	else
	{
		bOpen = true;
		g_OpenScene->limitrect = rect;	
		for each (CGameObject * var in enemyList)
		{
			var->bActive = true;
		}
		for each (CGameObject * var in itemList)
		{
			var->bActive = true;
		}
	}
}
