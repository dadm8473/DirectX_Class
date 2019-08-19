#include "DXUT.h"
#include "Header.h"

CAssetManager* gAssetManager;

void CAssetManager::InitAssets()
{
	playerTexture = new CTexture(L"EmptyProject", L"jpg", 1);
}

void CAssetManager::TermAssets()
{
	delete playerTexture;
}
