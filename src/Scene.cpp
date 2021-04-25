#include "Scene.hpp"


Scene::Scene()
{
	camera.offset = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };

	//call initializer that children will overwrite
	Initialize();
}

Scene::~Scene()
{
	//Get rid of all the unmanaged memory 
	for (GameObject* obj : all_objects)
	{
		delete obj;
	}
	all_objects.clear();
}

void Scene::Initialize()
{
	//Testing initializer
	//load textures
	
}

void Scene::update(float delta)
{
	for (GameObject* obj : all_objects)
	{
		obj->update(delta);
	}
}

void Scene::draw()
{
	//Tell raylib that we're gonna use the 2D mode
	BeginMode2D(camera);

	for (GameObject* obj : all_objects)
	{
		obj->draw();
	}

	EndMode2D();
}