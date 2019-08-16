#pragma once
class BackButton
{
public:
	BackButton();
	~BackButton();

	virtual void Start();
	virtual void OnCollision(CGameObject* CollisionObject);
};

