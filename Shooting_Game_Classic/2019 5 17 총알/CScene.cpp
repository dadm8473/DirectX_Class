#include "DXUT.h"
#include "Header.h"

CScene::CScene()
	: playerBulletList()
{
	player = new CPlayer(D3DXVECTOR2(512, 384));
	player->parentScene = this;
}

CScene::~CScene()
{
	if (player)
		delete player;

	for (list<CBullet*>::iterator it = playerBulletList.begin(); it != playerBulletList.end(); ++it)
		if (*it)
			delete (*it);
	playerBulletList.clear();

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

	if (GetKeyState('X') & 0x8000)
		player->Attack();

	player->Update(deltaTime);

	for (list<CBullet*>::iterator it = playerBulletList.begin(); it != playerBulletList.end(); ++it)
		(*it)->Update(deltaTime);
}

void CScene::Render(LPD3DXSPRITE sprite)
{
	player->Render(sprite);

	for (list<CBullet*>::iterator it = playerBulletList.begin(); it != playerBulletList.end(); ++it)
		(*it)->Render(sprite);
}

void CScene::MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
}
