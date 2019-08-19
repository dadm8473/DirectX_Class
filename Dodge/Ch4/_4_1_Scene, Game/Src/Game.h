#pragma once
class Game
{
public:
	ResourceManager m_ResourceManager;
	CInput m_Input;

	ID3DXFont*	m_pDXFont;

	float BestScore, TimeScore;

	Game();
	~Game();

	int Start();

	int Update(float dTime);

	int Render();

	int Destroy();
};

