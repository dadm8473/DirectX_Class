#pragma once
class CAssetManager
{
public:
	CTexture* playerTexture;
	CTexture* playerBulletTexture;

	void InitAssets();
	void TermAssets();
};

extern CAssetManager* gAssetManager;
