#include "DXUT.h"
#include "EnemyBullet.h"

void EnemyBullet::Init()
{
	// 스프라이트 렌더러 추가
	m_Renderer = new CSpriteRenderer();
	m_Renderer->Create(L"bullet_dummy_0.png");

	CVectorMove * VectorMove = new CVectorMove(this);
	VectorMove->fMoveSpeed = 300;
	VectorMove->fAngle = moveAngle;
	Components.push_front(VectorMove);

	BulletCollider * tempCollider = new BulletCollider(this, CL_BULLET);
	tempCollider->CheckLayers[CL_PLAYER] = true;
	Components.push_front(tempCollider);

	pivot = { m_Renderer->GetTextureInfo()->GetImageWidth() * 0.5f , m_Renderer->GetTextureInfo()->GetImageHeight() * 0.5f };
}
