#include "DXUT.h"
#include "CPlayer.h"

void CPlayer::Init()
{
	// 스프라이트 렌더러 추가
	m_Renderer = new CSpriteRenderer();
	m_Renderer->Create(L"TryWorld.jpg");

	CPlayerControl * PlayerControl = new CPlayerControl(this);
	PlayerControl->fMoveSpeed = 100;
	Components.push_front(PlayerControl);

	PlayerCollider * tempCollider = new PlayerCollider(this, CL_PLAYER);
	Components.push_front(tempCollider);

	position = { 512,384 };
	pivot = { 45, 37 };
}
