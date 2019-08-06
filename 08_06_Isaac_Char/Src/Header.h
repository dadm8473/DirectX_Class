#pragma once

enum OBJECT_TYPE
{
	GAMEOBJECT,
	ENEMY_BOSS,
	PLAYER,
	PLAYER_HEAD,
	ENEMY_BULLET,
	PLAYER_BULLET,	
	HUD_BG,
	HUD,
	UIOBJECT,
};

enum COLLIDER_LAYER
{
	CL_NONE,
	CL_PLAYER,
	CL_ENEMY,
	CL_ENEMY_BULLET,
	CL_PLAYER_BULLET,
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

#include "EnemyBullet.h"
#include "BulletSpawner.h"
#include "ChaseBullet.h"
#include "PlayerBullet.h"

#include "IsaacHead.h"
#include "Isaac.h"
extern Isaac * g_pPlayer;

#include "ChaseEnemy.h"
#include "Boss1.h"
#include "Boss2.h"

#include "Numeric.h"
#include "ScoreBoard.h"