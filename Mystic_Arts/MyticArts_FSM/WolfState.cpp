#include "DXUT.h"
#include "WolfState.h"

// ============================================================================================================================================

// Idle

// ============================================================================================================================================
void WolfIdle::EnterState(CWolf * pObject)
{
	if (pObject->nowState)
		pObject->nowState->ExitState(pObject);

	pObject->nowState = this;

	pObject->renderer->SetAni(0);
}

void WolfIdle::UpdateState(CWolf * pObject, float deltaTime)
{
	if (pObject->Move(deltaTime))
	{
		WolfMove::instance->EnterState(pObject);
		return;
	}
	if (pObject->playerCheck->bCheck)
	{
		WolfAttack::instance->EnterState(pObject);
		return;
	}
}

void WolfIdle::ExitState(CWolf * pObject)
{
}

// ============================================================================================================================================

// Move

// ============================================================================================================================================

void WolfMove::EnterState(CWolf * pObject)
{
	if (pObject->nowState)
		pObject->nowState->ExitState(pObject);

	pObject->nowState = this;

	pObject->renderer->SetAni(1);
}

void WolfMove::UpdateState(CWolf * pObject, float deltaTime)
{
	if (!pObject->Move(deltaTime))
	{
		// fallÀÌ¶û ³ª´²¼­ ºÁ¾ßµÊ
		WolfIdle::instance->EnterState(pObject);
		return;
	}
	if (pObject->playerCheck->bCheck)
	{
		WolfAttack::instance->EnterState(pObject);
		return;
	}
}

void WolfMove::ExitState(CWolf * pObject)
{
}

// ============================================================================================================================================

// Jump

// ============================================================================================================================================

void WolfJump::EnterState(CWolf * pObject)
{
	if (pObject->nowState)
		pObject->nowState->ExitState(pObject);

	pObject->nowState = this;

	pObject->renderer->SetAni(2);
}

void WolfJump::UpdateState(CWolf * pObject, float deltaTime)
{
}

void WolfJump::ExitState(CWolf * pObject)
{
}

// ============================================================================================================================================

// fall

// ============================================================================================================================================

void WolfFall::EnterState(CWolf * pObject)
{
	if (pObject->nowState)
		pObject->nowState->ExitState(pObject);

	pObject->nowState = this;

	pObject->renderer->SetAni(3);
}

void WolfFall::UpdateState(CWolf * pObject, float deltaTime)
{
	//pObject->renderer->SetAni(4);
}

void WolfFall::ExitState(CWolf * pObject)
{
}

// ============================================================================================================================================

// Attack

// ============================================================================================================================================

void WolfAttack::EnterState(CWolf * pObject)
{
	if (pObject->nowState)
		pObject->nowState->ExitState(pObject);

	pObject->nowState = this;

	pObject->scale.x = (pObject->playerCheck->player->position.x - pObject->position.x) /
		abs(pObject->playerCheck->player->position.x - pObject->position.x);

	pObject->renderer->SetAni(5);

	pObject->enemyAttackCollider->bCollision = true;
	pObject->enemyAttackCollider->attackVector = { 1,0.6 };
	pObject->enemyAttackCollider->attackPower = 200;

	pObject->force = D3DXVECTOR2(30 * pObject->scale.x, 15);
}

void WolfAttack::UpdateState(CWolf * pObject, float deltaTime)
{
	if (!pObject->renderer->bAnimation)
	{
		{
			WolfIdle::instance->EnterState(pObject);
			return;
		}
	}
}

void WolfAttack::ExitState(CWolf * pObject)
{
	pObject->enemyAttackCollider->bCollision = false;
}

// ============================================================================================================================================

// Hitted

// ============================================================================================================================================

void WolfHitted::EnterState(CWolf * pObject)
{
	if (pObject->nowState)
		pObject->nowState->ExitState(pObject);

	pObject->nowState = this;

	pObject->renderer->SetAni(6);
}

void WolfHitted::UpdateState(CWolf * pObject, float deltaTime)
{
}

void WolfHitted::ExitState(CWolf * pObject)
{
}

// ============================================================================================================================================

// Down

// ============================================================================================================================================

void WolfDown::EnterState(CWolf * pObject)
{
	if (pObject->nowState)
		pObject->nowState->ExitState(pObject);

	pObject->nowState = this;

	pObject->renderer->SetAni(7);
}

void WolfDown::UpdateState(CWolf * pObject, float deltaTime)
{
}

void WolfDown::ExitState(CWolf * pObject)
{
}
