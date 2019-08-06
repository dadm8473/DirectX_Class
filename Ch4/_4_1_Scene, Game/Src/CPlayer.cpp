#include "DXUT.h"
#include "CPlayer.h"

void CPlayer::Init()
{
	// 스프라이트 렌더러 추가
	m_Renderer = new CSpriteRenderer();
	m_Renderer->Create(L"ariplane_dummy.png");

	CPlayerControl * PlayerControl = new CPlayerControl(this);
	PlayerControl->fMoveSpeed = 400;
	Components.push_front(PlayerControl);

	PlayerCollider * tempCollider = new PlayerCollider(this, CL_PLAYER);
	Components.push_front(tempCollider);

	position = { 512,384 };
	pivot = { m_Renderer->GetTextureInfo()->GetImageWidth() * 0.5f , m_Renderer->GetTextureInfo()->GetImageHeight() * 0.5f };
}
