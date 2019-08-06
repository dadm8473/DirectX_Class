#include "DXUT.h"
#include "InGameScene.h"


InGameScene::InGameScene()
	: timer(0), time(0.02f), sum(0)
{
}


InGameScene::~InGameScene()
{
}

int InGameScene::Start()
{
	Scene::Start();

	g_Game.TimeScore = 0;

	g_pPlayer = new CPlayer();
	//g_pPlayer->Start();

	//EnemyBullet * temp;

	//for (int i = 0; i < 25; i++)
	//{
	//	temp = new EnemyBullet;
	//	int x = rand() % 1024;
	//	int y = rand() % 2;
	//	temp->position = D3DXVECTOR2(x, y * 768);
	//}

	//for (int i = 25; i < 50; i++)
	//{
	//	temp = new EnemyBullet;
	//	int x = rand() % 2;
	//	int y = rand() % 768;
	//	temp->position = D3DXVECTOR2(x * 1024, y);
	//}

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

	timer += deltaTime;
	if (timer > time)
	{
		for (int i = 0; i < 36; ++i)
		{
			EnemyBullet * temp;
			temp = new EnemyBullet;
			temp->position = D3DXVECTOR2(100, 100);
			temp->moveAngle = (sum * 1) + (i * 10);
		}

		for (int i = 0; i < 36; ++i)
		{
			EnemyBullet * temp;
			temp = new EnemyBullet;
			temp->position = D3DXVECTOR2(100, 100);
			temp->moveAngle = 360 - (sum * 1) - (i * 10);
		}

		sum++;
		timer = 0;
	}

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

	return 0;
}
