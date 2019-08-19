#include "DXUT.h"
#include "TitleControl.h"

void CTitleControl::Update(float deltaTime)
{
	if (g_Game.m_Input.KeyDown(VK_RETURN))
		g_OpenScene->bNextScene = true;
}
