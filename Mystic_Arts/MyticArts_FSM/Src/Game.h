#pragma once
class Game
{
public:
	MousePoint * mouse = NULL; //¡Ú¡Ú¡Ú

	ResourceManager m_ResourceManager;
	CInput Input;

	ID3DXFont*	m_pDXFont;

	float windowWidth;
	float windowHeight;

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

