#include "DXUT.h"
#include "InGameScene.h"


InGameScene::InGameScene()
{
}


InGameScene::~InGameScene()
{
}

int InGameScene::Start()
{
	Scene::Start();

	g_Game.TimeScore = 0;
	g_Game.BulletCount = 0;

	g_pPlayer = new CPlayer();
	
	for (int i = 0; i < 4; ++i)
	{
		BulletSpawner* spawner;
		spawner = new BulletSpawner;
		spawner->position = {(float)260 * i + 70, 100 };
	}

	return 0;
}

int InGameScene::Update(float deltaTime)
{
	if (bNextScene)
	{
		TitleScene * title = new TitleScene;

		title->Start();
		title->Update(deltaTime);
		return 0;
	}

	g_Game.TimeScore += deltaTime;
	if (g_Game.TimeScore > g_Game.BestScore)
		g_Game.BestScore = g_Game.TimeScore;

	Scene::Update(deltaTime);
	return 0;
}

int InGameScene::Render()
{
	Scene::Render();

	RECT rc;

	TCHAR buffer[100];
	memset(buffer, 0, sizeof(buffer));

	_stprintf_s(buffer, _T("FPS : %.2lf , dTime : %lf"), DXUTGetFPS());
	::SetRect(&rc, 0, 0, 500, 100);
	g_Game.m_pDXFont->DrawText(NULL, buffer, -1, &rc, 0, D3DXCOLOR(1, 1, 1, 1));

	_stprintf_s(buffer, _T("BestScore : %.2lf / NowScroe : %.2lf"), g_Game.BestScore, g_Game.TimeScore);
	::SetRect(&rc, 300, 50, 1000, 200);
	g_Game.m_pDXFont->DrawText(NULL, buffer, -1, &rc, 0, D3DXCOLOR(1, 1, 1, 1));

	_stprintf_s(buffer, _T("Bullet : %d"), g_Game.BulletCount);
	::SetRect(&rc, 800, 50, 1000, 200);
	g_Game.m_pDXFont->DrawText(NULL, buffer, -1, &rc, 0, D3DXCOLOR(1, 1, 1, 1));
	

	return 0;
}