#include "Scene.hpp"


Scene::Scene()
{
	camera.offset = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };
	camera.target = { 0,0 };
	camera.zoom = 1;

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
	//load default texture, no reason not to have it in vram
	AssetManager::GetAssetManager()->RequestTexture("resources/defaultTexture.png");

	//create a test object 
	GameObject* obj = new GameObject(ColliderType::None);
	all_objects.push_back(obj);
	obj->SetPosition({ 0,0 });
	obj->SetVelocity({ 1,1 });
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

	DrawLineV({ -1000, -1000 }, { 1000, 1000 }, BLACK);
	DrawLineV({ -1000, 1000 }, { 1000, -1000 }, BLACK);

	for (GameObject* obj : all_objects)
	{
		obj->draw();
	}

	EndMode2D();
}