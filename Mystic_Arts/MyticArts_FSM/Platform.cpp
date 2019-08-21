#include "DXUT.h"
#include "Platform.h"


Platform::Platform()
{

}


Platform::~Platform()
{
}

void Platform::Start()
{
	renderer = new CSpriteRenderer(L"Platform", L"Assets/Images/Map/PlatformTest", L"png", false);
	renderer->rect = new RECT;
	SetRect(renderer->rect, 0, 0, platformScale.x, renderer->GetTextureInfo().Height);


	type = PLATFORM;
	CreateRigidBody(D3DXVECTOR2(0, -50), D3DXVECTOR2(platformScale.x, platformScale.y));
	

	CreateCollider(CL_PLATFORM, D3DXVECTOR2(0, -50), D3DXVECTOR2(platformScale.x, platformScale.y));

	gravity = 0;

	pivot.y = 1;
	pivot.x = 0.5 *  platformScale.x / renderer->GetTextureInfo().Width;
}
