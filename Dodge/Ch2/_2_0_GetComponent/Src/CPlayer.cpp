#include "DXUT.h"
#include "CPlayer.h"

void CPlayer::Init()
{
	// 스프라이트 렌더러 추가
	m_Renderer = new CSpriteRenderer();
	m_Renderer->Create(L"TryWorld.jpg");

	Component * test = new Component(this);

	Components.push_front(test);
	Component* a = GetComponent<Component>();
	a->Start();

	position = { 512,384 };
	pivot = { 45, 37 };
}
