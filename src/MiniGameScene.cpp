#include "MiniGameScene.hpp"

MiniGameScene::MiniGameScene(std::function<void(void)> success_callback, std::function<void(void)> failure_callback) : Scene()
{
	successCallback = success_callback;
	failureCallback = failure_callback;
} 

void MiniGameScene::Initialize()
{

}

void MiniGameScene::update(float delta)
{
	Scene::update(delta);
}

void MiniGameScene::draw()
{
	Scene::draw();
}

void MiniGameScene::success()
{
	SceneManager::GetSceneManager()->PopScene();
	if(successCallback != nullptr)
		successCallback();
}

void MiniGameScene::failure()
{
	SceneManager::GetSceneManager()->PopScene();
	if(failureCallback != nullptr)
		failureCallback();
}