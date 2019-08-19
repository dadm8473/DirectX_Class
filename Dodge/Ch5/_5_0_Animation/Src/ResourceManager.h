#pragma once
#include <map>

typedef std::map<const TCHAR *, CTexture *> TextureMap;

class ResourceManager
{
private:
	CTexture* LoadTexture(const TCHAR* key, const TCHAR* fileName, const TCHAR* extName, int TotalFrame = 1);
	TextureMap m_TextureMap;

public:
	CTexture* GetTexture(const TCHAR * key, const TCHAR * fileName, const TCHAR* extName, int TotalFrame = 1);
	void Destroy();
};

