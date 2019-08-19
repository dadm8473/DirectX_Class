#pragma once
class CTexture
{
public:
	LPDIRECT3DTEXTURE9 * m_pTex;
	D3DXIMAGE_INFO m_Img;
	int totalFrame;

	CTexture(const TCHAR* fileName, const TCHAR* extName, int TotalFrame = 1);
	virtual ~CTexture();

	virtual void Destroy();

	void GetImageRect(RECT* pRc);
};