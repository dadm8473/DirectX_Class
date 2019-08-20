#pragma once

enum OBJECT_TYPE
{
	PLATFORM,
	GAMEOBJECT,
	HUD,
	UIOBJECT,
};

enum COLLIDER_LAYER
{
	CL_NONE,
	CL_UNIT,
	CL_ENEMY,
	CL_PLAYERATTACK,
	CL_PLATFORM,
	CL_MOUSE,
	CL_MAX,
};

extern bool bRigidbodyRender;

#include <tchar.h>

#include "CTexture.h"
#include "CInput.h"

#include "CSpriteRenderer.h"
#include "CGameObject.h"

#include "MousePoint.h"

#include "ResourceManager.h"
#include "ObjectManager.h"
#include "CollisionManager.h"

#include "Game.h"
extern Game g_Game;

#include "Scene.h"
extern Scene * g_OpenScene;
#include "TitleScene.h"
#include "InGameScene.h"

#include "HPBar.h"
#include "Numeric.h"
#include "ScoreBoard.h"

#include "Platform.h"

#include "CState.h"
#include "CHeroAttackCollider.h"
#include "HeroState.h"
#include "CHero.h"

#include "CScarecrow.h"