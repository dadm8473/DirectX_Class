#include "DXUT.h"
#include "ResourceManager.h"

CTexture * ResourceManager::LoadTexture(const TCHAR * sFile)
{
	CTexture* pTexture = new CTexture;
	pTexture->Create(sFile);
	m_TextureMap.insert(TextureMap::value_type(sFile, pTexture));

	return pTexture;
}

CTexture * ResourceManager::ReleasTexture()
{
	for (map<const TCHAR *, CTexture *>::iterator it = m_TextureMap.begin(); it != m_TextureMap.end();)
		if(it->second)
			it = m_TextureMap.erase(it);

	return nullptr;
}

CTexture * ResourceManager::GetTexture(const TCHAR * sFile)
{
	if (m_TextureMap[sFile] == NULL)
		return LoadTexture(sFile);
	else
		return m_TextureMap.at(sFile);
}
