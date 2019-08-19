#include "DXUT.h"
#include "CTransform.h"

CTransform::CTransform()
{
	position = { 0, 0 };
	scale = { 1, 1 };
	pivot = { 0,0 };
	fRot = 0;
	D3DXMatrixIdentity(&mWorld);
}

void CTransform::Start()
{
}

void CTransform::Update(float deltaTime)
{
	D3DXVECTOR2 pos = position - pivot;
	D3DXMatrixTransformation2D(&mWorld, &pivot, 0, &scale, &pivot,
		D3DXToRadian(fRot), &pos);
}

void CTransform::Render()
{
}

void CTransform::Destroy()
{
}

void CTransform::Translate(D3DXVECTOR2 vTrans)
{
	position += vTrans;
}
