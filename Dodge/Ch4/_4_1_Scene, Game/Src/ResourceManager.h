#pragma once
#include <map>

typedef std::map<const TCHAR *, CTexture *> TextureMap;

class ResourceManager
{
private:
	CTexture* LoadTexture(const TCHAR * sFile);
	
	TextureMap m_TextureMap;

public:
	CTexture* GetTexture(const TCHAR * sFile);
	CTexture* ReleasTexture();
};

