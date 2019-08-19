#include "DXUT.h"
#include "ScoreBoard.h"

void ScoreBoard::Start()
{
	for (int i = 0; i < 5; ++i)
	{
		Score[i] = new Numeric;
		Score[i]->position = { 900 + 20.f * i, 100.f };

		BestScore[i] = new Numeric;
		BestScore[i]->position = { 30 + 20.f * i, 100.f };
	}
}

void ScoreBoard::Update(float deltaTime)
{
	CGameObject::Update(deltaTime);

	int score = g_Game.TimeScore * 100;

	for (int i = 0; i < 5; ++i)
	{
		int test = pow(10, 4 - i);
		int n = score / pow(10, 4 - i);

		if(Score[i]->renderer)
			Score[i]->renderer->SetAni(n);
		score -= n * pow(10, 4 - i);
	}

	score = g_Game.BestScore * 100;

	for (int i = 0; i < 5; ++i)
	{
		int test = pow(10, 4 - i);
		int n = score / pow(10, 4 - i);

		if (BestScore[i]->renderer)
			BestScore[i]->renderer->SetAni(n);
		score -= n * pow(10, 4 - i);
	}
}
