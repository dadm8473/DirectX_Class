#pragma once

#include <typeinfo>
#include <tchar.h>

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

#include "ResourceManager.h"

#include "ObjectManager.h"

#include "CollisionManager.h"

#include "Game.h"
extern Game g_Game;

#include "Scene.h"
extern Scene * g_OpenScene;

#include "TitleScene.h"

#include "InGameScene.h"

#include "CVectorMove.h"
#include "BulletCollider.h"
#include "EnemyBullet.h"

#include "PlayerCollider.h"
#include "CPlayerControl.h"
#include "CPlayer.h"

#include "TitleControl.h"
#include "Title.h"

extern CPlayer * g_pPlayer;