#include "DXUT.h"
#include "Game.h"


Game::Game()
{
	BestScore = 0; TimeScore = 0;
	BulletCount = 40;
	timeScale = 1;
}

Game::~Game()
{
}

int Game::Start()
{
	if (FAILED(D3DXCreateFont(DXUTGetD3D9Device()
		, 20, 0
		, FW_DEMIBOLD, 1, FALSE
		, HANGUL_CHARSET
		, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_DONTCARE
		, _T("±Ã¼­Ã¼")
		, &m_pDXFont)))
		return -1;


	TitleScene* StartScene = new TitleScene;
	StartScene->Start();

	return 0;
}

int Game::Update(float deltaTime)
{
	m_Input.Update();

	unscaledTime = deltaTime;
	deltaTime *= timeScale;

	if (g_OpenScene)
		g_OpenScene->Update(deltaTime);

	return 0;
}

int Game::Render()
{

	if (g_OpenScene)
		g_OpenScene->Render();

	return 0;
}

int Game::Destroy()
{
	SAFE_RELEASE(m_pDXFont);

	m_ResourceManager.Destroy();

	if (g_OpenScene)
		g_OpenScene->Destroy();

	return 0;
}
