#pragma once
#include "IComponent.h"

class CTransform :
	public IComponent
{
public:
	CTransform();


	D3DXVECTOR2 position;
	D3DXVECTOR2 scale;
	D3DXVECTOR2 pivot;
	float fRot;
	D3DXMATRIX mWorld;

	std::list<IComponent *> Components;

	template<typename T>
	T* GetComponent() {
		for each (IComponent * val in Components)
		{
			if (typeid(T) == typeid(*val))
			{
				return (T*)val;
			}
		}

		MessageBoxA(DXUTGetHWND(), "Component Not Included", "Err", MB_ICONERROR);
		return NULL;
	}

	virtual void Start();
	virtual void Update(float deltaTime);
	virtual void Render();
	virtual void Destroy();
	
	virtual void Translate(D3DXVECTOR2 vTrans);
};

