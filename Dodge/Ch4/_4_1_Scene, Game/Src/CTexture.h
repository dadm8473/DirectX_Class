#pragma once
class CTexture
{
protected:
	D3DXIMAGE_INFO m_Img;
	LPDIRECT3DTEXTURE9 m_pTex;


public:
	CTexture();
	virtual ~CTexture();

	virtual int Create(const WCHAR* sFile);
	virtual void Destroy();

	int GetImageWidth();
	int GetImageHeight();
	void GetImageRect(RECT* pRc);

	LPDIRECT3DTEXTURE9 GetTexture();
};