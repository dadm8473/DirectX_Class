#include "DXUT.h"
#include "TitleScene.h"


TitleScene::TitleScene()
{
}


TitleScene::~TitleScene()
{
}

int TitleScene::Start()
{
	Scene::Start();

	Title * title = new Title;

	return 0;
}

int TitleScene::Update(float deltaTime)
{
	if (bNextScene)
	{
		InGameScene * ingame = new InGameScene;

		ingame->Start();
		ingame->Update(deltaTime);
		return 0;
	}

	Scene::Update(deltaTime);
	return 0;
}
