#include "DXUT.h"
#include "GolemState.h"

// ============================================================================================================================================

// Idle

// ============================================================================================================================================
void GolemIdle::EnterState(CGolem * pObject)
{
	if (pObject->nowState)
		pObject->nowState->ExitState(pObject);

	pObject->nowState = this;

	pObject->renderer->SetAni(0);
}

void GolemIdle::UpdateState(CGolem * pObject, float deltaTime)
{
	if (pObject->Move(deltaTime))
	{
		GolemMove::instance->EnterState(pObject);
		return;
	}
	if (pObject->playerCheck->bCheck)
	{
		GolemAttack2::instance->EnterState(pObject);
		return;
	}
}

void GolemIdle::ExitState(CGolem * pObject)
{
}

// ============================================================================================================================================

// Move 

// ============================================================================================================================================
void GolemMove::EnterState(CGolem * pObject)
{
	if (pObject->nowState)
		pObject->nowState->ExitState(pObject);

	pObject->nowState = this;

	pObject->renderer->SetAni(1);
}

void GolemMove::UpdateState(CGolem * pObject, float deltaTime)
{
	if (!pObject->Move(deltaTime))
	{
		GolemIdle::instance->EnterState(pObject);
		return;
	}
	if (pObject->playerCheck->bCheck)
	{
		GolemAttack2::instance->EnterState(pObject);
		return;
	}
}

void GolemMove::ExitState(CGolem * pObject)
{
}

// ============================================================================================================================================

// Attack 1

// ============================================================================================================================================
void GolemAttack1::EnterState(CGolem * pObject)
{
	if (pObject->nowState)
		pObject->nowState->ExitState(pObject);

	pObject->nowState = this;

	timer = 0;

	if (pObject->playerCheck->player)
		pObject->scale.x = (pObject->playerCheck->player->position.x - pObject->position.x) /
						abs(pObject->playerCheck->player->position.x - pObject->position.x);

	pObject->renderer->SetAni(2);

	bAttack = false;
}

void GolemAttack1::UpdateState(CGolem * pObject, float deltaTime)
{
	if(bAttack)
		pObject->enemyAttackCollider->bCollision = false;

	timer += deltaTime;

	if (timer > 0.5)
	{
		if (!bAttack)
		{
			bAttack = true;
			pObject->renderer->SetAni(3);
			pObject->enemyAttackCollider->bCollision = true;
			pObject->enemyAttackCollider->collisionNum++;
			pObject->enemyAttackCollider->attackVector = { 3,1 };
			pObject->enemyAttackCollider->attackPower = 1000;
			timer = 0;
		}
		else
		{
			GolemIdle::instance->EnterState(pObject);
			return;
		}
	}
}

void GolemAttack1::ExitState(CGolem * pObject)
{
	pObject->enemyAttackCollider->bCollision = false;
}

// ============================================================================================================================================

// Attack 2

// ============================================================================================================================================
void GolemAttack2::EnterState(CGolem * pObject)
{
	if (pObject->nowState)
		pObject->nowState->ExitState(pObject);

	pObject->nowState = this;

	timer = 0;

	if (pObject->playerCheck->player)
		pObject->scale.x = (pObject->playerCheck->player->position.x - pObject->position.x) /
						abs(pObject->playerCheck->player->position.x - pObject->position.x);

	pObject->renderer->SetAni(4);

	bAttack = false;
}

void GolemAttack2::UpdateState(CGolem * pObject, float deltaTime)
{
	if (bAttack)
		pObject->enemyAttackCollider->bCollision = false;

	timer += deltaTime;

	if (timer > 0.5)
	{
		if (!bAttack)
		{
			bAttack = true;
			pObject->renderer->SetAni(5);
			pObject->enemyAttackCollider->bCollision = true;
			pObject->enemyAttackCollider->collisionNum++;
			pObject->enemyAttackCollider->attackVector = { 0,3 };
			pObject->enemyAttackCollider->attackPower = 800;
			timer = 0;
		}
		else
		{
			//GolemIdle::instance->EnterState(pObject);
			GolemAttack1::instance->EnterState(pObject);
			return;
		}
	}
}

void GolemAttack2::ExitState(CGolem * pObject)
{
	pObject->enemyAttackCollider->bCollision = false;
}
