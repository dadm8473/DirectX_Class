#pragma once

class CSpriteRenderer
{
public:
	CSpriteRenderer(const TCHAR* key, const TCHAR* fileName, const TCHAR* extName, bool p_bAnimation, int p_TotalIndex = 0, int p_TotalFrame = 0, float p_Delay = 0);
	~CSpriteRenderer() { Destroy(); }

	CTexture * pTexture;
	LPD3DXSPRITE sprite;
	int r, g, b, a;
	RECT * rect;

	bool bAnimation;
	int nowIndex;
	float delay;
	float delayTimer;

	bool* roop;
	int* startFrame;
	int* frameAmount;
	
	int nowFrame;

	virtual void Update(float deltaTime);
	virtual void Render(D3DXMATRIX mWorld);
	virtual void Destroy();

	void SetIndex(int p_index, int p_startFrame, int p_frameAmount, bool p_roop);

	void SetAni(int index);

	virtual D3DXIMAGE_INFO GetTextureInfo()
	{
		return pTexture->m_Img;
	}
};
