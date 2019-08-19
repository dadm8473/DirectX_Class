#include "DXUT.h"
#include "Header.h"

CAssetManager* gAssetManager;

void CAssetManager::InitAssets()
{
	playerTexture = new CTexture(L"1", L"jpg", 3);
}

void CAssetManager::TermAssets()
{
	delete playerTexture;
}
