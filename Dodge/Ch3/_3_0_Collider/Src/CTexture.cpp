#include "DXUT.h"
#include "CTexture.h"

CTexture::CTexture()
{
	m_pTex = nullptr;
}

CTexture::~CTexture()
{
	Destroy();
}

INT CTexture::Create(const WCHAR* sFile)
{
	if (FAILED(D3DXCreateTextureFromFileEx(
		DXUTGetD3D9Device()		// Device
		, sFile					//  파일경로
		, D3DX_DEFAULT
		, D3DX_DEFAULT
		, 1
		, 0
		, D3DFMT_UNKNOWN
		, D3DPOOL_MANAGED
		, D3DX_FILTER_NONE
		, D3DX_FILTER_NONE
		, 0x00FFFFFF
		, &m_Img
		, NULL
		, &m_pTex
	)))
	{
		MessageBox(DXUTGetHWND()
			, L"Create Texture Failed"
			, L"Err"
			, MB_OK
		);


		return -1;
	}

	return 0;
}

void CTexture::Destroy()
{
	if (m_pTex)
	{
		SAFE_RELEASE(m_pTex);
		m_pTex = NULL;
	}
}

INT CTexture::GetImageWidth()
{
	return m_Img.Width;
}

INT CTexture::GetImageHeight()
{
	return m_Img.Height;
}

void CTexture::GetImageRect(RECT* pRc)
{
	pRc->left = 0;
	pRc->top = 0;
	pRc->right = GetImageWidth();
	pRc->bottom = GetImageHeight();
}

LPDIRECT3DTEXTURE9 CTexture::GetTexture()
{
	return m_pTex;
}
