#include "DXUT.h"
#include "ScoreBoard.h"

void ScoreBoard::Start()
{
	for (int i = 0; i < 5; ++i)
	{
		Score[i] = new Numeric;
		Score[i]->position = { 900 + 20.f * i, -100.f };
	}

	for (int i = 0; i < 5; ++i)
	{
		BestScore[i] = new Numeric;
		BestScore[i]->position = { 104 + 20.f * i, -100.f };
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
		if(n>9)
			Score[i]->renderer->SetAni(n);


		if(Score[i]->renderer)
			Score[i]->renderer->SetAni(n);
		score -= n * pow(10, 4 - i);
	}

	int bestScore = g_Game.BestScore * 100;

	if (g_Game.BestScore < g_Game.TimeScore)
	{
		for (int i = 0; i < 5; ++i)
		{
			int test = pow(10, 4 - i);
			int n = score / pow(10, 4 - i);
			if (n > 9)
				BestScore[i]->renderer->SetAni(n);


			if (BestScore[i]->renderer)
				BestScore[i]->renderer->SetAni(n);
			score -= n * pow(10, 4 - i);
		}
	}
	else
	{
		for (int i = 0; i < 5; ++i)
		{
			int test = pow(10, 4 - i);
			int n = bestScore / pow(10, 4 - i);
			if (n > 9)
				BestScore[i]->renderer->SetAni(n);


			if (BestScore[i]->renderer)
				BestScore[i]->renderer->SetAni(n);
			bestScore -= n * pow(10, 4 - i);
		}
	}
}
