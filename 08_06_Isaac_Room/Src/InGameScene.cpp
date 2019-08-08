#include "DXUT.h"
#include "InGameScene.h"


InGameScene::InGameScene()
{
}


InGameScene::~InGameScene()
{
}

CGameObject * g_nowRoom;

int InGameScene::Start()
{
	Scene::Start();

	ScoreBoard * scoreboard = new ScoreBoard;

	g_Game.TimeScore = 0;
	g_Game.BulletCount = 0;

	g_pPlayer = new Isaac();

	//EnemyBullet * temp;

	//for (int i = 0; i < g_Game.BulletCount * 0.5; i++)
	//{
	//	temp = new EnemyBullet;
	//	int x = rand() % 1024 - 512;
	//	int y = rand() % 2;
	//	temp->position = D3DXVECTOR2(x, -384 + y * 768);
	//}

	//for (int i = 0; i < g_Game.BulletCount * 0.5; i++)
	//{
	//	temp = new EnemyBullet;
	//	int x = rand() % 2;
	//	int y = rand() % 768 - 384;
	//	temp->position = D3DXVECTOR2(-512 + x * 1024, y);
	//}

	//BulletSpawner* temp2 = new BulletSpawner;


	Room * Roomtemp = new Room;
	Roomtemp->position = { 0,0 };

	CItem * item = new CItem(1);
	Roomtemp->SetItem(item, D3DXVECTOR2(-100, 100));

	item = new CItem(2);
	Roomtemp->SetItem(item, D3DXVECTOR2(100, 100));














	Roomtemp = new Room;
	Roomtemp->position = { 1024,0 };
	Boss1 * boss1 = new Boss1;
	Roomtemp->SetEnemy(boss1, D3DXVECTOR2(0, 200));

	Roomtemp = new Room;
	Roomtemp->position = { 1024,768 };
	Boss2 * boss2 = new Boss2;
	Roomtemp->SetEnemy(boss2, D3DXVECTOR2(0, 200));

	Roomtemp = new Room;
	Roomtemp->position = { 2048,768 };

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
