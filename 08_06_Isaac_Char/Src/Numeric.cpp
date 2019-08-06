#include "DXUT.h"
#include "Numeric.h"

void Numeric::Start()
{
	type = UIOBJECT;
	// 스프라이트 렌더러 추가
	renderer = new CSpriteRenderer(L"Numeric", L"Assets/Images/UI/Numeric", L"png", true, 10, 10, 1);
	renderer->SetIndex(0, 0, 1, false);
	renderer->SetIndex(1, 1, 1, false);
	renderer->SetIndex(2, 2, 1, false);
	renderer->SetIndex(3, 3, 1, false);
	renderer->SetIndex(4, 4, 1, false);
	renderer->SetIndex(5, 5, 1, false);
	renderer->SetIndex(6, 6, 1, false);
	renderer->SetIndex(7, 7, 1, false);
	renderer->SetIndex(8, 8, 1, false);
	renderer->SetIndex(9, 9, 1, false);

	scale = { 0.4, 0.4 };
}

void Numeric::Update(float deltaTime)
{
	CGameObject::Update(deltaTime);
}
