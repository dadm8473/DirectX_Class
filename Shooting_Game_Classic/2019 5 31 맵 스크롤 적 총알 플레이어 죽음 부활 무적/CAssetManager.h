#pragma once
class CAssetManager
{
public:
	CTexture* playerTexture;
	CTexture* playerBulletTexture;

	CTexture* enemyTexture;

	CTexture* bossTexture;

	CTexture* mapTexture;

	void InitAssets();
	void TermAssets();
};

extern CAssetManager* gAssetManager;
