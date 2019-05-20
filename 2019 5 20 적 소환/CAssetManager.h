#pragma once
class CAssetManager
{
public:
	CTexture* playerTexture;
	CTexture* playerBulletTexture;

	CTexture* enemyTexture;

	void InitAssets();
	void TermAssets();
};

extern CAssetManager* gAssetManager;
