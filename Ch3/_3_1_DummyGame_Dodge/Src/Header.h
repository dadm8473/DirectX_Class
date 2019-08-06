#pragma once

#include <typeinfo>

#include "CTexture.h"
#include "CInput.h"
extern CInput g_Input;

#include "IComponent.h"
#include "IRenderer.h"
#include "Renderer.h"
#include "CTransform.h"
#include "CGameObject.h"
#include "Component.h"
#include "Collider.h"

#include "CSpriteRenderer.h"

#include "CollisionManager.h"
extern CollisionManager g_CollisionManager;


#include "CVectorMove.h"
#include "BulletCollider.h"
#include "EnemyBullet.h"

#include "PlayerCollider.h"
#include "CPlayerControl.h"
#include "CPlayer.h"

extern CPlayer * g_pPlayer;