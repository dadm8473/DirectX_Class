#include "DXUT.h"
#include "Door.h"


Door::Door()
{
}


Door::~Door()
{
}

void Door::Start()
{
	type = BG_DOOR;
	// ½ºÇÁ¶óÀÌÆ® ·»´õ·¯ Ãß°¡
	renderer = new CSpriteRenderer(L"Door", L"Assets/Images/BG/BossDoor_", L"png", true, 2, 2, 0);
	renderer->SetIndex(0, 0, 1, false);	// ´ÝÈù ¹®
	renderer->SetIndex(1, 1, 1, false); // ¿­¸° ¹®

	pivot.y = 0.33;

	CreateCollider(CL_NONE, 50);
	SetCollision(CL_PLAYER);
	bCollision = false;

	switch (dir)
	{
	case DOWN:
		scale.y *= -1;
		break;
	case RIGHT:
		fRot = 90;
		break;
	case UP:
		break;
	case LEFT:
		fRot = -90;
		break;
	default:
		break;
	}
}

void Door::OnCollision(CGameObject * CollisionObject)
{
	//char temp[100];
	//memset(temp, 0, sizeof(temp));
	//sprintf(temp, "GAME CLEAR. CLEAR TIME : %.2lf", g_Game.TimeScore);

	//MessageBoxA(DXUTGetHWND(), temp, "TryWorld MSG Box", MB_OK);

	//g_OpenScene->bNextScene = true;
	D3DXVECTOR2 vtemp = nextRoom - position;
	D3DXVec2Normalize(&vtemp, &vtemp);

	CollisionObject->position += vtemp * 150;

	g_OpenScene->MoveCamera(nextRoom, 3000);

	for each (CGameObject * var in g_OpenScene->m_ObjectList)
	{
		if (var->type == BG_ROOM)
		{
			((Room*)var)->CheckPlayer();
		}
	}
}
