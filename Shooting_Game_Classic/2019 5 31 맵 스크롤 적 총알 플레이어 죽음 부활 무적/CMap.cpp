#include "DXUT.h"
#include "Header.h"

CMap::CMap()
{
	for (int i = 0; i < 2; ++i)
	{
		mapLayer[i] = CMatrix();
		mapLayer[i].position.y = 768 * i;
	}
}

void CMap::Update(float deltaTime)
{
	for (int i = 0; i < 2; ++i)
	{
		mapLayer[i].position.y += 256 * deltaTime;

		if (mapLayer[i].position.y >= 768)
			mapLayer[i].position.y -= 768 * 2;

		mapLayer[i].Update(deltaTime);
	}
}

void CMap::Render(LPD3DXSPRITE sprite)
{
	for (int i = 0; i < 2; ++i)
		mapLayer[i].Draw(sprite, gAssetManager->mapTexture);
}
