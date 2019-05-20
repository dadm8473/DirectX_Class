#include "DXUT.h"
#include "Header.h"

CTexture::CTexture(LPCWSTR filename, LPCWSTR extname, int maxScene)
{
	_textures = new LPDIRECT3DTEXTURE9[maxScene];
	this->maxScene = maxScene;

	for (int i = 0; i < maxScene; ++i)
	{
		wchar_t temp[256];
		wsprintf(temp, L"%s%02d.%s", filename, i, extname);

		D3DXGetImageInfoFromFile(temp, &imageInfo);

		if (FAILED(D3DXCreateTextureFromFileEx(
			DXUTGetD3D9Device(),		// 디바이스
			temp,						// 파일 경로
			imageInfo.Width,			// 그림 너비
			imageInfo.Height,			// 그림 높이
			1,							// 밉맵 수준
			0,							// 사용 목적
			D3DFMT_A8R8G8B8,			// 텍스쳐 포맷
			D3DPOOL_MANAGED,			// 메모리 폴
			D3DX_DEFAULT,				// 텍스쳐 필터
			D3DX_DEFAULT,				// 밉맵 필터
			0,							// 알파 키값
			NULL,						// 이미지 정보
			NULL,						// 팔레트
			&_textures[i]				// 텍스쳐
		)))
		{
			MessageBox(DXUTGetHWND(),
				temp,
				L"이미지를 불러오지 못했습니다",
				MB_OK);
		}

		if (i == 0)
		{
			width = imageInfo.Width;
			height = imageInfo.Height;
		}
	}
}

CTexture::~CTexture()
{
	for (int i = 0; i < maxScene; ++i)
		if (_textures[i])
			_textures[i]->Release();

	delete[] _textures;
}
