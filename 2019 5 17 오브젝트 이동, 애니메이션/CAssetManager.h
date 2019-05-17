#pragma once
class CAssetManager
{
public:
	CTexture* playerTexture;

	void InitAssets();
	void TermAssets();
};

extern CAssetManager* gAssetManager;
