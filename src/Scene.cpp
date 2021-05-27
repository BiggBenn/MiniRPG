#include "Scene.hpp"

#include "Egg.hpp"
#include "Weed.hpp"
#include "npcs/TestNpc.hpp"
#include "npcs/Jenkins.hpp"
#include "LogChopSpot.hpp"

Scene::Scene()
{
	//set up the camera
	camera.offset = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };
	camera.target = { 0,0 };
	camera.zoom = 1;

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

	/*//create a test object
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
	obj3->SetCollider({ Rect, {0,0,300,50}, 0 });*/


	//spawn the player
	Player* player = new Player(this);
	all_objects.push_back(player);

	//SPAWN EGG
	for (int i = 0; i < StoryProgress::goalEggCount; i++)
	{
		Egg* egg = new Egg();
		all_objects.push_back(egg);
		egg->SetPosition({ (float)GetRandomValue(-400, 400), (float)GetRandomValue(-300,300) });
		egg->SetSize({ 30,50 });
	}

	Egg* eggo = new Egg();
	all_objects.push_back(eggo);
	eggo->SetZ(50);
	eggo->SetPosition({ 0,0 });
	eggo->SetSize({ 30,50 });

	GameObject* ob = new GameObject();
	all_objects.push_back(ob);
	ob->SetZ(-50);
	ob->SetPosition({ 0,0 });
	ob->SetSize({100, 100});

	//spawn weed
	Weed* weed = new Weed();
	all_objects.push_back(weed);
	weed->SetPosition({ 100, 100 });

	TestNpc* testNpc = new TestNpc();
	all_objects.push_back(testNpc);
	testNpc->SetPosition({ -100, -100 });

	//spawn log chop spot
	LogChopSpot* spot = new LogChopSpot();
	all_objects.push_back(spot);
	spot->SetPosition({ -200, -50 });

	//spawn jenkins
	Jenkins* jenkins = new Jenkins();
	all_objects.push_back(jenkins);
	jenkins->SetPosition({ 200, -150 });
}

void Scene::update(float delta)
{
	bool sortVector = false;
	std::vector<GameObject*> toDelete;
	for (GameObject* obj : all_objects)
	{
		obj->update(delta);
		//note if the object has its delete flag set
		if (obj->DeleteFlag)
		{
			toDelete.push_back(obj);
		}
		if (obj->zChanged)
		{
			sortVector = true;
			obj->zChanged = false;
		}
	}

	for (GameObject* obj : toDelete)
	{
		//delete both the object and the reference in all_objects
		all_objects.erase(std::remove(all_objects.begin(), all_objects.end(), obj), all_objects.end());
		delete obj;
	}
	toDelete.clear();


	if (sortVector)
	{
		//sort the vector by z
		std::sort(all_objects.begin(), all_objects.end(), GameObject::CompareZ);
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