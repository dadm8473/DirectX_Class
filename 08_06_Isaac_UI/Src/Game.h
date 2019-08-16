#pragma once
class Game
{
public:
	ResourceManager m_ResourceManager;
	CInput m_Input;

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

extern int bullet_damage;
extern float p_Attack_Speed;

