#pragma once
class CPlayerControl 
	: public Component
{
public:
	CPlayerControl(CTransform * p_trnasform) :Component(p_trnasform) {};

	float fMoveSpeed = 0;
	
	virtual void Start();
	virtual void Update(float deltaTime);
	virtual void Destroy();
};

