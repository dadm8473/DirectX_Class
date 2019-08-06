#pragma once

enum OBJECT_TYPE
{
	GAMEOBJECT,
	HUD,
	UIOBJECT,
};

enum COLLIDER_LAYER
{
	CL_NONE,
	CL_PLAYER,
	CL_BULLET,
	CL_MAX,
};

#include <tchar.h>

#include "CTexture.h"
#include "CInput.h"
extern CInput g_Input;

#include "CSpriteRenderer.h"
#include "CGameObject.h"

#include "ResourceManager.h"
#include "ObjectManager.h"
#include "CollisionManager.h"

#include "Game.h"
extern Game g_Game;

#include "Scene.h"
extern Scene * g_OpenScene;
#include "TitleScene.h"
#include "InGameScene.h"

#include "Title.h"

#include "HPBar.h"
#include "CPlayer.h"
extern CPlayer * g_pPlayer;

#include "EnemyBullet.h"
#include "BulletSpawner.h"
#include "ChaseBullet.h"

#include "Numeric.h"
#include "ScoreBoard.h"