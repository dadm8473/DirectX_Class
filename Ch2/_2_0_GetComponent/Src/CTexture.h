#pragma once
class CTexture
{
protected:
	D3DXIMAGE_INFO m_Img;
	LPDIRECT3DTEXTURE9 m_pTex;


public:
	CTexture();
	virtual ~CTexture();

	virtual INT Create(const WCHAR* sFile);
	virtual void Destroy();

	INT GetImageWidth();
	INT GetImageHeight();
	void GetImageRect(RECT* pRc);

	LPDIRECT3DTEXTURE9 GetTexture();
};