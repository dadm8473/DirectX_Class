#include "DXUT.h"
#include "Header.h"

CScene::CScene()
{
	player = new CPlayer(D3DXVECTOR2(512, 384));
}

CScene::~CScene()
{
	if (player)
		delete player;
}

void CScene::Update(float deltaTime)
{
	if (GetKeyState(VK_LEFT) & 0x8000)
		player->position.x -= 400 * deltaTime;

	if (GetKeyState(VK_RIGHT) & 0x8000)
		player->position.x += 400 * deltaTime;

	if (GetKeyState(VK_UP) & 0x8000)
		player->position.y -= 400 * deltaTime;

	if (GetKeyState(VK_DOWN) & 0x8000)
		player->position.y += 400 * deltaTime;

	player->Update(deltaTime);
}

void CScene::Render(LPD3DXSPRITE sprite)
{
	player->Render(sprite);
}

void CScene::MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
}
