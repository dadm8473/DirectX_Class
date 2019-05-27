#pragma once
class CAssetManager
{
public:
	CTexture* playerTexture;
	CTexture* playerBulletTexture;

	CTexture* enemyTexture;

	CTexture* bossTexture;

	void InitAssets();
	void TermAssets();
};

extern CAssetManager* gAssetManager;
