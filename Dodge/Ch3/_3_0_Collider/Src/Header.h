#pragma once

#include <typeinfo>

#include "CInput.h"
extern CInput g_Input;

#include "IComponent.h"
#include "IRenderer.h"
#include "Renderer.h"
#include "CTransform.h"
#include "CGameObject.h"
#include "Component.h"
#include "Collider.h"
#include "CircleCollider.h"
#include "BoxCollider.h"

#include "CollisionManager.h"
extern CollisionManager g_CollisionManager;

#include "CTexture.h"
#include "CSpriteRenderer.h"

#include "CPlayerControl.h"
#include "CPlayer.h"