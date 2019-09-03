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

	CScarecrow * temp2 = new CScarecrow;

	CGolem * temp3 = new CGolem;
	temp3->position = { 100, 0 };

	CWolf * temp4 = new CWolf;
	temp4->position = { 0, -200 };

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

	Wall * wall = new Wall;
	wall->position = {-g_Game.windowWidth * 0.5f, 0 };
	
	wall = new Wall;
	wall->position = { g_Game.windowWidth * 0.5f, 0 };

	return 0;
}

int TitleScene::Update(float deltaTime)
{
	if (bNextScene)
	{
		InGameScene * ingame = new InGameScene;//�ڡڡ�

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

	//�ڡڡ�
	RECT rc;

	TCHAR buffer[100];
	memset(buffer, 0, sizeof(buffer));
	_stprintf_s(buffer, _T("x : %.2lf , y : %2lf"), g_Game.mouse->position.x, g_Game.mouse->position.y); 
	::SetRect(&rc, 0, 0, 500, 100);
	g_Game.m_pDXFont->DrawText(NULL, buffer, -1, &rc, 0, D3DXCOLOR(1, 1, 1, 1));


	_stprintf_s(buffer, _T("FPS : %.2lf , dTime : %lf"), DXUTGetFPS(), g_Game.unscaleTime);
	::SetRect(&rc, 0, 100, 500, 200);
	g_Game.m_pDXFont->DrawText(NULL, buffer, -1, &rc, 0, D3DXCOLOR(1, 1, 1, 1));

	InvalidateRgn(DXUTGetHWND(), NULL, false);
	return 0;
}
