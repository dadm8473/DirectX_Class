#include "DXUT.h"
#include "TitleScene.h"


TitleScene::TitleScene()
{
}


TitleScene::~TitleScene()
{
}

int TitleScene::Start()
{
	Scene::Start();

	CHero * temp = new CHero;

	Platform * Platformtemp = new Platform;
	Platformtemp->position = { 0,-320 };
	Platformtemp->platformScale = { 1024, 60 };
	
	Platformtemp = new Platform;
	Platformtemp->position = { -250,0 };
	Platformtemp->platformScale = { 300, 60 };
	
	Platformtemp = new Platform;
	Platformtemp->position = { 250, 0 };
	Platformtemp->platformScale = { 300, 60 };

	Platformtemp = new Platform;
	Platformtemp->position = { 0, 150 };
	Platformtemp->platformScale = { 100, 60 };

	Platformtemp = new Platform;
	Platformtemp->position = { 0, -150 };
	Platformtemp->platformScale = { 300, 60 };

	return 0;
}

int TitleScene::Update(float deltaTime)
{
	if (bNextScene)
	{
		InGameScene * ingame = new InGameScene;//¡Ú¡Ú¡Ú

		ingame->Start();
		ingame->Update(deltaTime);
		return 0;
	}

	Scene::Update(deltaTime);
	return 0;
}

int TitleScene::Render()
{
	Scene::Render();

	//¡Ú¡Ú¡Ú
	RECT rc;

	TCHAR buffer[100];
	memset(buffer, 0, sizeof(buffer));
	_stprintf_s(buffer, _T("x : %.2lf , y : %2lf"), g_Game.mouse->position.x, g_Game.mouse->position.y); 
	::SetRect(&rc, 0, 0, 500, 100);
	g_Game.m_pDXFont->DrawText(NULL, buffer, -1, &rc, 0, D3DXCOLOR(1, 1, 1, 1));

	InvalidateRgn(DXUTGetHWND(), NULL, false);
	return 0;
}
