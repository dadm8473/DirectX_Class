#include "DXUT.h"
#include "CTexture.h"

CTexture::CTexture(const TCHAR* fileName, const TCHAR* extName, int p_totalFrame)
{
	m_pTex = new LPDIRECT3DTEXTURE9[p_totalFrame];
	totalFrame = p_totalFrame;

	memset(&m_Img, 0, sizeof(m_Img));

	for (int i = 0; i < totalFrame; i++)
	{
		TCHAR temp[256];
		if(totalFrame != 1)
			wsprintf(temp, L"%s%02d.%s", fileName, i, extName);
		else
			wsprintf(temp, L"%s.%s", fileName, extName);

		if (FAILED(D3DXCreateTextureFromFileEx(
			DXUTGetD3D9Device()		// Device
			, temp					//  파일경로
			, D3DX_DEFAULT
			, D3DX_DEFAULT
			, 1
			, 0
			, D3DFMT_UNKNOWN
			, D3DPOOL_MANAGED
			, D3DX_FILTER_POINT
			, D3DX_FILTER_NONE
			, 0x00FFFFFF
			, &m_Img
			, NULL
			, &m_pTex[i]
		)))
		{
			MessageBox(DXUTGetHWND()
				, L"Create Texture Failed"
				, L"Err"
				, MB_OK
			);
			return;
		}
	}
}

CTexture::~CTexture()
{
	Destroy();
}

void CTexture::Destroy()
{
	if (m_pTex)
	{
		for(int i = 0 ; i < totalFrame; ++i)
			SAFE_RELEASE(m_pTex[i]);

		SAFE_DELETE_ARRAY(m_pTex);
	}
}
void CTexture::GetImageRect(RECT* pRc)
{
	pRc->left = 0;
	pRc->top = 0;
	pRc->right = m_Img.Width;
	pRc->bottom = m_Img.Height;
}