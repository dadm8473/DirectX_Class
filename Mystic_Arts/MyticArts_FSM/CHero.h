#pragma once
#include "CGameObject.h"
#include "CState.h"

enum HERO_ANI_INDEX
{
	IDLE,			// 0 :  0,4  - idle
	MOVESTART,		// 1 :  5,9  - move start
	MOVE,			// 2 : 10,14 - move
	JUMP,			// 3 : 15,17 - jump
	JUMPTOFALL,		// 4 : 18,19 - jump to fall
	FALL,			// 5 : 20,21 - fall
	FALLATTACK,		// 6 : 22,22 - fall attack
	ATTACK1,		// 7 : 42,43 - attack 1
	ATTACK2,		// 8 : 44,46 - attack 2
	ATTACK3,		// 9 : 47,53 - attack 3
	ATTACK4,		//10 : 54,57 - attack 4(돌려차기)
	ATTACK5,		//11 : 58,62 - attack 5(다리후리기)
	ATTACK6,		//12 : 63,66 - attack 6(올려차기)
	ATTACK7,		//13 : 63,67 - attack 7(올려차 내려찍기)
	ATTACK8DASH,	//14 : 67,68 - attack 8 dash
	ATTACK8,		//15 : 67,68 - attack 8(장풍)
	ATTACK9,		//16 : 74,80 - attack 9(밀쳐내기)
	JUMPATTACK1,	//17 : 26,28 - jump attack 1
	JUMPATTACK2,	//18 : 29,32 - jump attack 2(돌려차기)
	JUMPATTACK3,	//19 : 33,36 - jump attack 3(내려찍기)
};

enum INPUT_DIR
{
	LEFT,
	UP,
	RIGHT,
	DOWN,
};

class CHero :
	public CGameObject
{
public:
	CHero();
	~CHero();

	CState<CHero> * nowState = NULL;

	float moveSpeed;
	bool bFlip = true;
	bool bDoubleJump = false;
	bool bJumpAttack = false;

	int specialIndex = -1;
	float inputTimer = 0;
	int prevInput = -1;
	int nowInput = -1;

	D3DXVECTOR2 prevMove;
	D3DXVECTOR2 prevPos;

	CHeroAttackCollider * heroAttackCollider;

	virtual void Start();
	virtual void Update(float deltaTime);

	bool Move(float deltaTime);
	int SetSpecialIndex();
};