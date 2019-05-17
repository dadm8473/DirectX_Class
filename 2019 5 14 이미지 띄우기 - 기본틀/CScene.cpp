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
	player->Update(deltaTime);
}

void CScene::Render(LPD3DXSPRITE sprite)
{
	player->Render(sprite);
}

void CScene::MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
}
