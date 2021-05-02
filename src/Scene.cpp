#include "Scene.hpp"


Scene::Scene()
{
	//set up the camera
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
	GameObject* obj = new GameObject();
	all_objects.push_back(obj);
	obj->SetPosition({ 100,20 });
	//obj->SetVelocity({ -100,-100 });
	obj->SetCollider({ Circle, {0}, 50 });

	GameObject* obj2 = new GameObject();
	all_objects.push_back(obj2);
	obj2->SetPosition({ -200, -50 });
	obj2->SetCollider({ Rect, {0,0,100,100}, 0 });

	GameObject* obj3 = new GameObject();
	all_objects.push_back(obj3);
	obj3->SetPosition({ -200, -50 });
	obj3->SetSize({ 300,50 });
	obj3->SetCollider({ Rect, {0,0,300,50}, 0 });


	//spawn the player
	Player* player = new Player(this);
	all_objects.push_back(player);
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


void Scene::GetNearbyObjects(Vector2 coordinates, float range, std::vector<GameObject*>* outputVector)
{
	//Like said in function description, this will use the naive approach of iterating through all objects. This should be fine, as only the player really wants to know
	//where other things are, and there aren't all that many of them. Most likely not worth the overhead of a quadrant system
	float rangesquared = range * range;
	for (GameObject* gobj : all_objects)
	{
		if (Vector2LengthSquared(gobj->GetPosition() - coordinates) < rangesquared)
		{
			outputVector->push_back(gobj);
		}
	}
}