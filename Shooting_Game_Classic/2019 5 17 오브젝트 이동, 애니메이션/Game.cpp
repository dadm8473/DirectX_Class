#include "DXUT.h"
#include "Header.h"

LPD3DXSPRITE gSprite;
CScene* gScene;

void Init()
{
	D3DXCreateSprite(DXUTGetD3D9Device(), &gSprite);

	// 이미지를 불러오기
	gAssetManager = new CAssetManager();
	gAssetManager->InitAssets();

	// 씬 불러오기
	gScene = new CScene();
}

void Term()
{
	// 이미지 소멸자
	gAssetManager->TermAssets();

	if (gSprite)
		gSprite->Release();

	// 씬 소멸자
	if (gScene)
		delete gScene;
}

void Update(float deltaTime)
{
	// 씬 업데이트
	if (gScene)
		gScene->Update(deltaTime);
}

void Render()
{
	gSprite->Begin(D3DXSPRITE_ALPHABLEND);

	// 씬 그려주기
	if (gScene)
		gScene->Render(gSprite);

	gSprite->End();
}

void MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// 씬 MsgProc받아주기
	if (gScene)
		gScene->MsgProc(uMsg, wParam, lParam);
}
