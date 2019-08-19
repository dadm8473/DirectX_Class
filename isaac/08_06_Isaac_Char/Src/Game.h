#pragma once
class Game
{
public:
	ResourceManager m_ResourceManager;
	CInput m_Input;

	ID3DXFont*	m_pDXFont;

	int BulletCount;
	float BestScore, TimeScore;

	float timeScale = 1;
	float unscaleTime;

	Game();
	~Game();

	int Start();

	int Update(float dTime);

	int Render();

	int Destroy();
};

