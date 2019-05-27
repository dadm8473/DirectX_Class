#include "DXUT.h"
#include "Header.h"

CAssetManager* gAssetManager;

void CAssetManager::InitAssets()
{
	playerTexture = new CTexture(L"1", L"jpg", 3);
	playerBulletTexture = new CTexture(L"Bullet", L"png", 1);

	enemyTexture = new CTexture(L"enemy", L"png", 1);

	bossTexture = new CTexture(L"boss", L"png", 1);
}

void CAssetManager::TermAssets()
{
	delete playerTexture;
	delete playerBulletTexture;

	delete enemyTexture;

	delete bossTexture;
}
