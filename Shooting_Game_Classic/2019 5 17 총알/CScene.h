#pragma once
class CScene
{
public:
	list<CBullet*> playerBulletList;

	CPlayer* player;

public:
	CScene();	// Init()
	~CScene();	// Term()
	virtual void Update(float deltaTime);	// Update
	virtual void Render(LPD3DXSPRITE sprite);	// Render
	virtual void MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam);	 // MsgProc
};
