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

	if (g_Game.Input.KeyPress(VK_DOWN))
	{
		HeroGuard::instance->EnterState(pObject);
	}

	if (g_Game.Input.KeyDown('S'))
	{
		HeroJump::instance->EnterState(pObject);
		return;
	}

	if (g_Game.Input.KeyDown('A'))
	{
		if (pObject->SetSpecialIndex() != -1)
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
		if (pObject->SetSpecialIndex() != -1)
			HeroSpecailAttack::instance->EnterState(pObject);
		else
			HeroAttack::instance->EnterState(pObject);
		return;
	}

	if (g_Game.Input.KeyDown('S'))
	{
		if (g_Game.Input.KeyPress(VK_DOWN))
		{
			HeroGuard::instance->EnterState(pObject);
		}
		else
			HeroJump::instance->EnterState(pObject);
		return;
	}

	if (!pObject->Move(deltaTime))
	{
		HeroIdle::instance->EnterState(pObject);
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

	pObject->velocity.y = 800;

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
			pObject->velocity.y = 800;
		else
			pObject->velocity.y = 800;

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
	pObject->heroAttackCollider->bCollision = true;
	pObject->heroAttackCollider->collisionNum++;
	pObject->heroAttackCollider->attackVector = { 1,0 };
	pObject->heroAttackCollider->attackPower = 300;

	combo = 0;
	comboInput = 0;
	timer = 0;
}

void HeroAttack::UpdateState(CHero * pObject, float deltaTime)
{
	// 선입력
	if (g_Game.Input.KeyDown('A'))
	{
		if (pObject->SetSpecialIndex() != -1)
		{
			HeroSpecailAttack::instance->EnterState(pObject);
			return;
		}
		else if (comboInput < 3)
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
		{
			pObject->renderer->SetAni(7 + combo);
			pObject->heroAttackCollider->bCollision = true;
			pObject->heroAttackCollider->collisionNum++;
		}
	}

	// 특정 콤보 시 이동가능
	if (combo > 1)
	{
		pObject->moveSpeed = 80;
		pObject->heroAttackCollider->attackVector = { 1, 0.4 };
		pObject->heroAttackCollider->attackPower = 1000;
	}

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
	pObject->heroAttackCollider->bCollision = false;
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

	pObject->renderer->SetAni(17);
	combo = 0;
	comboInput = 0;
	timer = 0;
	under_Attack = false;

	pObject->heroAttackCollider->bCollision = true;
	pObject->heroAttackCollider->collisionNum++;
	pObject->heroAttackCollider->attackVector = { 0.1,0.5 };
	pObject->heroAttackCollider->attackPower = 200;

	pObject->gravity = 0.1;
	pObject->velocity.y = 0;
	pObject->bJumpAttack = false;
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
			pObject->renderer->SetAni(19);
			pObject->heroAttackCollider->collisionNum++;
			pObject->heroAttackCollider->attackVector = { 1, -1 };
			pObject->heroAttackCollider->attackPower = 2000;
		}
		else
		{
			pObject->renderer->SetAni(18);
			pObject->heroAttackCollider->collisionNum++;
			pObject->heroAttackCollider->attackVector = { 2,0.2 };
			pObject->heroAttackCollider->attackPower = 2000;
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
	pObject->heroAttackCollider->bCollision = false;
}


// ============================================================================================================================================

// SPECIIAL ATTACK

// ============================================================================================================================================
void HeroSpecailAttack::EnterState(CHero * pObject)
{
	if (pObject->nowState)
		pObject->nowState->ExitState(pObject);

	pObject->nowState = this;

	pObject->moveSpeed = 80;
	pObject->bFlip = false;

	pObject->heroAttackCollider->bCollision = true;
	pObject->heroAttackCollider->collisionNum++;
	//★★★★★
	// 공격 커멘드 입력 비 충족 시
	if (pObject->specialIndex == -1)
	{
		if (g_Game.Input.KeyPress(VK_DOWN))
		{
			pObject->specialIndex = 1;
			pObject->moveSpeed = 0;
		}
		else if (g_Game.Input.KeyPress(VK_UP))
		{
			pObject->specialIndex = 2;
			pObject->velocity.y = 800;
		}
		else
			pObject->specialIndex = 0;
	}
	else
		//★★★★★
		// 공격 커멘드 입력 비 충족 시
	{
		pObject->prevInput = -1;
		pObject->nowInput = -1;
		switch (pObject->specialIndex)
		{
		case 0:
			pObject->velocity.x += pObject->scale.x * 2000;
			break;
		case 2:
			pObject->velocity.x += pObject->scale.x * 1200;
			break;
		case 3:
			pObject->velocity.x += pObject->scale.x * 1500;
			pObject->velocity.y = 200;
			break;
		case 4:
			break;
		default:
			break;
		}
	}

	switch (pObject->specialIndex)
	{
	case 0:
		pObject->heroAttackCollider->attackVector = { 1,0.2 };
		pObject->heroAttackCollider->attackPower = 3000;
		break;
	case 2:
		pObject->heroAttackCollider->attackVector = { 0.1,1 };
		pObject->heroAttackCollider->attackPower = 1000;
		break;
	case 3:
		pObject->heroAttackCollider->attackVector = { 1, 0.2 };
		pObject->heroAttackCollider->attackPower = 1500;
		break;
	case 4:
		pObject->heroAttackCollider->attackVector = { 1,0.6 };
		pObject->heroAttackCollider->attackPower = 50;
		break;
	}

	pObject->renderer->SetAni(10 + pObject->specialIndex);
	timer = 0;
}

void HeroSpecailAttack::UpdateState(CHero * pObject, float deltaTime)
{
	if (timer > 0.4)
	{
		HeroIdle::instance->EnterState(pObject);
		return;
	}
	if (pObject->specialIndex == 4)
	{
		pObject->velocity.x += pObject->scale.x * 150;
	}
	else
		pObject->Move(deltaTime);

	timer += deltaTime;
}

void HeroSpecailAttack::ExitState(CHero * pObject)
{
	pObject->moveSpeed = 300;
	pObject->bFlip = true;
	pObject->heroAttackCollider->bCollision = false;
}

// ============================================================================================================================================

// Guard

// ============================================================================================================================================
void HeroGuard::EnterState(CHero * pObject)
{
	if (pObject->nowState)
		pObject->nowState->ExitState(pObject);

	pObject->nowState = this;

	pObject->moveSpeed = 0;
	pObject->bFlip = false;

	pObject->renderer->SetAni(20);
	pObject->mass = 10;
}

void HeroGuard::UpdateState(CHero * pObject, float deltaTime)
{
	// 지면 검사
	if (g_Game.Input.KeyUp(VK_DOWN))
	{
		HeroIdle::instance->EnterState(pObject);
		return;
	}
	if (g_Game.Input.KeyDown('A'))
	{
		HeroSpecailAttack::instance->EnterState(pObject);
		return;
	}
	if (g_Game.Input.KeyDown('S') && pObject->position.y > -300)
	{
		pObject->position.y -= 10;
		HeroFall::instance->EnterState(pObject);
	}
}

void HeroGuard::ExitState(CHero * pObject)
{
	pObject->moveSpeed = 300;
	pObject->bFlip = true;
	pObject->mass = 1;
}