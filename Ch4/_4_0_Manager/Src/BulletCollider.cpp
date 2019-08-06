#include "DXUT.h"

void BulletCollider::OnCollision(CGameObject * CollisionObject)
{
	MessageBoxA(DXUTGetHWND(), "GAME OVER", "TryWorld MSG Box", MB_OK);
	g_pPlayer = NULL;
	delete(CollisionObject);
}
