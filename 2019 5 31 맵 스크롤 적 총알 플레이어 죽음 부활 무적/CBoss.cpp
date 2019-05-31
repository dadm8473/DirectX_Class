#include "DXUT.h"
#include "Header.h"

CBoss::CBoss(D3DXVECTOR2 pos)
	: CMatrix(), maxHp(100), speed(256), isEnter(true), isPatternOn(false), patternNum(0),
	bulletCount(0), maxBullet(0), patternTime(1), patternTimer(0), attackTimer(0), attackTime(0),
	isDie(false), sum(0)
{
	hp = maxHp;

	position = pos;
	center = D3DXVECTOR2(100, 50);
}

void CBoss::Update(float deltaTime)
{
	if (isEnter)
	{
		// 보스가 위에서 등장
		position.y += speed * deltaTime;

		if (position.y >= 128)
		{
			position.y = 128;
			isEnter = false;
		}
	}
	else
	{
		if (isPatternOn == false)
		{
			patternTimer += deltaTime;
			if (patternTimer >= patternTime)
			{
				isPatternOn = true;
				patternTimer = 0;
				bulletCount = 0;
				sum = 0;

				switch (patternNum)
				{
				case 0:
					attackTime = 0.4f;
					maxBullet = 50;
					break;
				case 1:
					attackTime = 0.007f;
					maxBullet = 50;
					break;
				}
			}
		}
		else // isPatternOn 트루일 경우
		{
			attackTimer += deltaTime;
			if (attackTimer >= attackTime)
			{
				attackTimer = 0;

				switch (patternNum)
				{
				case 0:		// 1번 패턴
					switch (sum)
					{
					case 0:
						for (int i = 0; i < 30; i++)
							parentScene->enemyBulletList.push_back(new CBullet(position, 550, 180 + (i * 3)));
						sum = 1;
						break;
					case 1:
						for (int i = 0; i < 30; i++)
							parentScene->enemyBulletList.push_back(new CBullet(position, 550, 180 - (i * 3)));
						sum = 0;
						break;
					}

					if (++bulletCount >= maxBullet)
					{
						isPatternOn = false;
						patternNum++;
					}
					break;
				case 1:		// 2번 패턴
					for (int i = 0; i < 50; i++)
						for (int j = 0; j < 5; j++)
							parentScene->enemyBulletList.push_back(new CBullet(position, 550,  (144 + (j * 144))+(sum*60)  ));

					sum++;
					if (++bulletCount >= maxBullet)
					{
						isPatternOn = false;
						patternNum--;
					}
					break;
				}
			}
		}
	}

	CMatrix::Update(deltaTime);
}

void CBoss::Render(LPD3DXSPRITE sprite)
{
	Draw(sprite, gAssetManager->bossTexture);
}