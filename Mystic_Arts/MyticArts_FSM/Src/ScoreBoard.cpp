#include "DXUT.h"
#include "ScoreBoard.h"

void ScoreBoard::Start()
{
	for (int i = 0; i < 5; ++i)
	{
		Score[i] = new Numeric;
		Score[i]->fRot = fRot; //¡Ú¡Ú¡Ú
		Score[i]->position = D3DXVECTOR2(-90 + 45.f * i, 0 - fRot * 0.25 * i) + position; //¡Ú¡Ú¡Ú
	}
}

void ScoreBoard::Update(float deltaTime)
{
	CGameObject::Update(deltaTime);

	int score = g_Game.TimeScore; //¡Ú¡Ú¡Ú
	bool firstNum = false; //¡Ú¡Ú¡Ú

	for (int i = 0; i < 5; ++i)
	{
		int test = pow(10, 4 - i);
		int n = score / pow(10, 4 - i);

		if (n == 0) //¡Ú¡Ú¡Ú
		{
			if (firstNum == 0)
				Score[i]->bActive = false;
		}
		else
			firstNum = true;

		if(Score[i]->renderer)
			Score[i]->renderer->SetAni(n);
		score -= n * pow(10, 4 - i);
	}
}
