#include "SceneManager.hpp"

SceneManager* SceneManager::Singleton = nullptr;


SceneManager::SceneManager()
{

}

SceneManager* SceneManager::GetSceneManager()
{
	if (SceneManager::Singleton == nullptr)
	{
		Singleton = new SceneManager();
	}

	return Singleton;
}

void SceneManager::AddScene(Scene* scene)
{
	scenes.push_back(scene);
}

void SceneManager::PopScene()
{
	scenes.pop_back();
}

void SceneManager::update(float delta)
{
	//update the topmost scene
	scenes.back()->update(delta);
}

void SceneManager::draw()
{
	//Draw all scenes in sequence, lowest one at the front first
	for (Scene* scene : scenes)
	{
		scene->draw();
	}
}