#include "DXUT.h"
#include "Header.h"

LPD3DXSPRITE gSprite;
CScene* gScene;

void Init()
{
	D3DXCreateSprite(DXUTGetD3D9Device(), &gSprite);

	// �̹����� �ҷ�����
	gAssetManager = new CAssetManager();
	gAssetManager->InitAssets();

	// �� �ҷ�����
	gScene = new CScene();
}

void Term()
{
	// �̹��� �Ҹ���
	gAssetManager->TermAssets();

	if (gSprite)
		gSprite->Release();

	// �� �Ҹ���
	if (gScene)
		delete gScene;
}

void Update(float deltaTime)
{
	// �� ������Ʈ
	if (gScene)
		gScene->Update(deltaTime);
}

void Render()
{
	gSprite->Begin(D3DXSPRITE_ALPHABLEND);

	// �� �׷��ֱ�
	if (gScene)
		gScene->Render(gSprite);

	gSprite->End();
}

void MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// �� MsgProc�޾��ֱ�
	if (gScene)
		gScene->MsgProc(uMsg, wParam, lParam);
}
