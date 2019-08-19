#include "DXUT.h"
#include "HeroState.h"


// ============================================================================================================================================

// IDLE

// ============================================================================================================================================
void HeroIdle::EnterState(CHero * pObject)
{
	if (pObject->nowState)
		pObject->nowState->ExitState(pObject);

	pObject->nowState = this;

	pObject->renderer->SetAni(0);
}

void HeroIdle::UpdateState(CHero * pObject, float deltaTime)
{
	if (!pObject->bGround)
	{
		HeroFall::instance->EnterState(pObject);
		return;
	}
	if (g_Game.Input.KeyDown('S'))
	{
		if (g_Game.Input.KeyPress(VK_DOWN) && pObject->position.y > -300)
		{
			pObject->position.y -= 10;
			HeroFall::instance->EnterState(pObject);
		}
		else
			HeroJump::instance->EnterState(pObject);
		return;
	}
	if (g_Game.Input.KeyDown('A'))
	{
		if (g_Game.Input.KeyPress(VK_DOWN))
			HeroSpecailAttack::instance->EnterState(pObject);
		else
			HeroAttack::instance->EnterState(pObject);
		return;
	}
	if (pObject->Move(deltaTime))
	{
		HeroMove::instance->EnterState(pObject);
		return;
	}
}

void HeroIdle::ExitState(CHero * pObject)
{
}

// ============================================================================================================================================

// MOVE

// ============================================================================================================================================
void HeroMove::EnterState(CHero * pObject)
{
	if (pObject->nowState)
		pObject->nowState->ExitState(pObject);

	pObject->nowState = this;

	pObject->renderer->SetAni(1);
}

void HeroMove::UpdateState(CHero * pObject, float deltaTime)
{
	if (!pObject->bGround)
	{
		HeroFall::instance->EnterState(pObject);
		return;
	}
	if (g_Game.Input.KeyDown('A'))
	{
		HeroAttack::instance->EnterState(pObject);
		return;
	}
	if (!pObject->Move(deltaTime))
	{
		HeroIdle::instance->EnterState(pObject);
		return;
	}
	if (g_Game.Input.KeyDown('S'))
	{
		HeroJump::instance->EnterState(pObject);
		return;
	}

	if (!pObject->renderer->bAnimation)
		pObject->renderer->SetAni(2);

}

void HeroMove::ExitState(CHero * pObject)
{
}

// ============================================================================================================================================

// JUMP

// ============================================================================================================================================
void HeroJump::EnterState(CHero * pObject)
{
	if (pObject->nowState)
		pObject->nowState->ExitState(pObject);

	pObject->nowState = this;

	pObject->force.y += 50;

	pObject->renderer->SetAni(3);
}

void HeroJump::UpdateState(CHero * pObject, float deltaTime)
{
	if (pObject->velocity.y < 0)
	{
		HeroFall::instance->EnterState(pObject);
		return;
	}
	if (pObject->bGround)
	{
		HeroIdle::instance->EnterState(pObject);
		return;
	}

	pObject->Move(deltaTime);
	HeroInAir::instance->UpdateState(pObject, deltaTime);
}

void HeroJump::ExitState(CHero * pObject)
{
}

// ============================================================================================================================================

// FALL

// ============================================================================================================================================
void HeroFall::EnterState(CHero * pObject)
{
	if (pObject->nowState)
		pObject->nowState->ExitState(pObject);

	pObject->nowState = this;

	pObject->renderer->SetAni(4);
	jump2fall = true;
}

void HeroFall::UpdateState(CHero * pObject, float deltaTime)
{
	if (pObject->bGround)
	{
		HeroIdle::instance->EnterState(pObject);
		HeroJump::instance->isDoubleJump = false;
		HeroInAir::instance->isSkyAttack = false;
		return;
	}
	if (pObject->velocity.y < -300 && jump2fall)
	{
		pObject->renderer->SetAni(5);
		jump2fall = false;
	}

	pObject->Move(deltaTime);
	HeroInAir::instance->UpdateState(pObject, deltaTime);
}

void HeroFall::ExitState(CHero * pObject)
{
}

// ============================================================================================================================================

// InAir 

// ============================================================================================================================================

void HeroInAir::EnterState(CHero * pObject)
{
}

void HeroInAir::UpdateState(CHero * pObject, float deltaTime)
{
	index = pObject->renderer->nowIndex;

	if (g_Game.Input.KeyPress(VK_DOWN) && g_Game.Input.KeyDown('S'))
	{
		if(index == 3)
			HeroFall::instance->EnterState(pObject);
		pObject->velocity.y = -1000;
		return;
	}

	if (g_Game.Input.KeyDown('S') && (!HeroJump::instance->isDoubleJump))
	{
		/*if (pObject->nowState)
			pObject->nowState->ExitState(pObject);*/

		//pObject->nowState = this;

		if(index == 3)
			pObject->force.y += 40;
		else
			pObject->force.y += 70;

		pObject->renderer->SetAni(3);

		HeroJump::instance->isDoubleJump = true;
		return;
	}

	if (g_Game.Input.KeyDown('A') && !isSkyAttack)
	{
		HeroSkyAttack::instance->EnterState(pObject);
	}
}

void HeroInAir::ExitState(CHero * pObject)
{
	pObject->renderer->SetAni(index);
}

// ============================================================================================================================================

// ATTACK 

// ============================================================================================================================================
void HeroAttack::EnterState(CHero * pObject)
{
	if (pObject->nowState)
		pObject->nowState->ExitState(pObject);

	pObject->nowState = this;

	pObject->moveSpeed = 0;
	pObject->bFlip = false;

	pObject->renderer->SetAni(7);
	combo = 0;
	comboInput = 0;
	timer = 0;
}

void HeroAttack::UpdateState(CHero * pObject, float deltaTime)
{
	// 선입력
	if (g_Game.Input.KeyDown('A') && comboInput < 3)
	{
		comboInput++;
	}

	// 낙하 검사
	if (!pObject->bGround)
	{
		HeroFall::instance->EnterState(pObject);
		return;
	}

	// 선입력에 따른 콤보
	if (!pObject->renderer->bAnimation && combo < comboInput)
	{
		combo++;
		timer = 0;

		if (combo == 3)
		{
			HeroSpecailAttack::instance->EnterState(pObject);
			return;
		}
		else
			pObject->renderer->SetAni(7 + combo);
	}

	// 특정 콤보 시 이동가능
	if(combo > 1)
		pObject->moveSpeed = 80;

	// 시간제한으로 상태 해제
	if (timer > 0.3 && !pObject->renderer->bAnimation)
	{
		HeroIdle::instance->EnterState(pObject);
		return;
	}
	pObject->Move(deltaTime);

	timer += deltaTime;
}

void HeroAttack::ExitState(CHero * pObject)
{
	pObject->moveSpeed = 300;
	pObject->bFlip = true;
}

// ============================================================================================================================================

// SKY ATTACK

// ============================================================================================================================================

void HeroSkyAttack::EnterState(CHero * pObject)
{
	if (pObject->nowState)
		pObject->nowState->ExitState(pObject);

	pObject->nowState = this;

	pObject->moveSpeed = 0;
	pObject->bFlip = false;

	pObject->renderer->SetAni(20);
	combo = 0;
	comboInput = 0;
	timer = 0;
	under_Attack = false;
}

void HeroSkyAttack::UpdateState(CHero * pObject, float deltaTime)
{
	// 선입력
	if (g_Game.Input.KeyDown('A') && comboInput < 1)
	{
		comboInput++;
	}

	if (g_Game.Input.KeyDown('A') && g_Game.Input.KeyPress(VK_DOWN) && comboInput == 1)
		under_Attack = true;


	// 낙하 검사
	/*if (!pObject->bGround)
	{
		HeroFall::instance->EnterState(pObject);
		return;
	}*/

	// 선입력에 따른 콤보
	if (!pObject->renderer->bAnimation && combo < comboInput)
	{
		combo++;
		timer = 0;

		if (under_Attack && combo == 1)
		{
			pObject->renderer->SetAni(22);
		}
		else
		{
			pObject->renderer->SetAni(21);
		}
	}

	// 시간제한으로 상태 해제
	if (timer > 0.3 && !pObject->renderer->bAnimation)
	{
		HeroFall::instance->EnterState(pObject);
		HeroInAir::instance->isSkyAttack = true;
		HeroJump::instance->isDoubleJump = true;
		return;
	}
	//pObject->Move(deltaTime);

	timer += deltaTime;
	pObject->velocity = {0, 0};
	pObject->gravity = 0.7f;
}

void HeroSkyAttack::ExitState(CHero * pObject)
{
	pObject->moveSpeed = 300;
	pObject->bFlip = true;
	pObject->gravity = 1;
}


// ============================================================================================================================================

// SPECIIAL ATTACK

// ============================================================================================================================================
void HeroSpecailAttack::EnterState(CHero * pObject)
{
	if (pObject->nowState)
		pObject->nowState->ExitState(pObject);

	pObject->nowState = this;

	pObject->moveSpeed = 0;
	pObject->bFlip = false;

	if (g_Game.Input.KeyPress(VK_DOWN))
		index = 1;
	else if (g_Game.Input.KeyPress(VK_UP))
	{
		index = 2;
		pObject->force.y += 50;
	}
	else
	{
		index = 0;
		pObject->moveSpeed = 80;
	}

	pObject->renderer->SetAni(10 + index);

	timer = 0;
}

void HeroSpecailAttack::UpdateState(CHero * pObject, float deltaTime)
{
	/*if (!pObject->bGround)
	{
		HeroFall::instance->EnterState(pObject);
		return;
	}*/
	if (timer > 0.3 && !pObject->renderer->bAnimation)
	{
		HeroIdle::instance->EnterState(pObject);
		return;
	}
	pObject->Move(deltaTime);

	timer += deltaTime;
}

void HeroSpecailAttack::ExitState(CHero * pObject)
{
	pObject->moveSpeed = 300;
	pObject->bFlip = true;
}

