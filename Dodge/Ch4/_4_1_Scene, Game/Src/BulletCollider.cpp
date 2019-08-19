#include "DXUT.h"

void BulletCollider::OnCollision(CGameObject * CollisionObject)
{
	char temp[100];
	memset(temp, 0, sizeof(temp));

	sprintf(temp, "GAME OVER. Score : %.2lf", g_Game.TimeScore);

	MessageBoxA(DXUTGetHWND(), temp, "TryWorld MSG Box", MB_OK);
	g_pPlayer = NULL;
	delete(CollisionObject);
	g_OpenScene->bNextScene = true;
}
