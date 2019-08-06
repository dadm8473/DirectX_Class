#include "DXUT.h"
#include "BulletSpawner.h"

void BulletSpawner::Start()
{
	renderer = new CSpriteRenderer(L"Spawner", L"Assets/Images/Shooter0000", L"png", false);
	scale = { 0.2f, 0.2f };

	attackCount = 0;
	maxAttackCount = 20;

	attackTime = rand() % 3 + 1;
	attackTimer = 0.0f;

	movedir_x = 1;
}

void BulletSpawner::Update(float deltaTime)
{
	CGameObject::Update(deltaTime);

	position.x += 50 * deltaTime * movedir_x;  

	attackTimer += deltaTime;
	if (attackTimer > attackTime)
	{
		attackTimer = 0;
		attackTime = rand() % 4 + 1;

		bullet = new EnemyBullet;
		bullet->position = position;
		if (attackTime == 4)
		{
			bullet->isHoming = true;
			bullet-> renderer = new CSpriteRenderer(
				L"EnemyBullet_Homing", L"Assets/Images/Bullet/bullet_dummy_1", L"png", false);
		}
		attackCount++;

		g_Game.BulletCount++;

		movedir_x = -movedir_x;

		if (attackCount > maxAttackCount)
			bActive = true;
	}
}
