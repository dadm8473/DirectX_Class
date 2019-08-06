#include "DXUT.h"
#include "CPlayer.h"

void CPlayer::Init()
{
	// ��������Ʈ ������ �߰�
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
