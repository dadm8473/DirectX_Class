#include "DXUT.h"
#include "Wall.h"


void Wall::Start()
{
	type = WALL;
	CreateRigidBody(D3DXVECTOR2(0, 0), D3DXVECTOR2(10, g_Game.windowHeight));

	gravity = 0;
}
