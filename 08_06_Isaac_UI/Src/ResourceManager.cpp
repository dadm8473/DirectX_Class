#include "DXUT.h"
#include "ResourceManager.h"

CTexture * ResourceManager::LoadTexture(const TCHAR* key, const TCHAR* fileName, const TCHAR* extName, int TotalFrame)
{
	CTexture* pTexture = new CTexture(fileName, extName, TotalFrame);
	m_TextureMap.insert(TextureMap::value_type(key, pTexture));

	return pTexture;
}

CTexture * ResourceManager::GetTexture(const TCHAR* key, const TCHAR* fileName, const TCHAR* extName, int totalFrame)
{
	if (m_TextureMap.find(key) == m_TextureMap.end())
		return LoadTexture(key, fileName, extName, totalFrame);
	else
		return m_TextureMap.at(key);
}

void ResourceManager::Destroy()
{
	for (TextureMap::iterator it = m_TextureMap.begin(); it != m_TextureMap.end();++it)
	{
		SAFE_DELETE(it->second);
	}
	m_TextureMap.clear();
}
