#include "DXUT.h"
#include "EndingScene.h"


EndingScene::EndingScene()
{
}


EndingScene::~EndingScene()
{
}

int EndingScene::Start()
{
	Scene::Start();

	Ending * ending = new Ending;

	return 0;
}

int EndingScene::Update(float deltaTime)
{
	if (bNextScene)
	{
		TitleScene * title = new TitleScene;

		title->Start();
		title->Update(deltaTime);
		return 0;
	}

	Scene::Update(deltaTime);
	return 0;
}
