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

	ScoreBoard * temp3 = new ScoreBoard;

	g_Game.TimeScore = 0;
	g_Game.BulletCount = 100;

	g_pPlayer = new CPlayer();

	EnemyBullet * temp;

	for (int i = 0; i < g_Game.BulletCount * 0.5; i++)
	{
		temp = new EnemyBullet;
		int x = rand() % 1024 - 512;
		int y = rand() % 2;
		temp->position = D3DXVECTOR2(x, -384 + y * 768);
	}

	for (int i = 0; i < g_Game.BulletCount * 0.5; i++)
	{
		temp = new EnemyBullet;
		int x = rand() % 2;
		int y = rand() % 768 - 384;
		temp->position = D3DXVECTOR2(-512 + x * 1024, y);
	}

	BulletSpawner* temp2 = new BulletSpawner;

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
