#pragma once

template <typename Object>
class CState
{
public:
	virtual void EnterState(Object * pObject) {}
	virtual void UpdateState(Object * pObject, float deltaTime) {}
	virtual void ExitState(Object * pObject) {}
};

