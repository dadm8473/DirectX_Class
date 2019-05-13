#include "DXUT.h"
#include "Game.h"

LPD3DXSPRITE gSprite;
LPDIRECT3DTEXTURE9 gTexture;

void Init()
{
	// 스프라이트 생성
	D3DXCreateSprite(DXUTGetD3D9Device(), &gSprite);

	// 이미지 한 장 불러오기
	D3DXCreateTextureFromFile(
		DXUTGetD3D9Device(),
		L"EmptyProject.jpg",
		&gTexture
	);
}

void Term()
{
	// 소멸
	if (gTexture)
		gTexture->Release();
	if (gSprite)
		gSprite->Release();
}

void Update(float deltaTime)
{
}

void Render()
{
	gSprite->Begin(D3DXSPRITE_ALPHABLEND);

	gSprite->Draw(gTexture,
		NULL, NULL, NULL,
		D3DCOLOR_ARGB(255, 255, 255, 255));

	gSprite->End();
}

void MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
}
