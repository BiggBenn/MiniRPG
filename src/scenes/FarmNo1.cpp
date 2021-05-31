#include "scenes/FarmNo1.hpp"

#include "ExitPoint.hpp"
#include "StoryProgress.hpp"

void FarmNo1::Initialize()
{
	//note that the player visited jenkins already
	StoryProgress::farmsVisited[0] = true;

	//spawn jenkins somewhere
	Jenkins* jenkins = new Jenkins();
	all_objects.push_back(jenkins);

	//spawn the player
	Player* player = new Player(this);
	all_objects.push_back(player);

	//spawn exit point
	ExitPoint* point = new ExitPoint();
	all_objects.push_back(point);
	point->SetPosition({ -200, 0 });

	//create colliders
	GameObject* A1 = new GameObject();
	A1->SetCollider({ ColliderType::Rect, {0,0,30, 1000} });
	A1->SetSize({ 30,1000 });
	A1->SetPosition({ -400,0 });
	all_objects.push_back(A1);
}
