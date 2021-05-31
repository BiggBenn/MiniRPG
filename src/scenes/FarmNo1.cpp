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
	A1->SetCollider({ ColliderType::Rect, {0,0,30, 1800} });
	A1->SetSize({ 30,1800 });
	A1->SetPosition({ -800,0 });
	all_objects.push_back(A1);

	GameObject* A2 = new GameObject();
	A2->SetCollider({ ColliderType::Rect, {0,0,300, 30} });
	A2->SetSize({ 300, 30 });
	A2->SetPosition({ -650, -900 });
	all_objects.push_back(A2);

	GameObject* A3 = new GameObject();
	A3->SetCollider({ ColliderType::Rect, {0,0,300, 30} });
	A3->SetSize({ 300, 30 });
	A3->SetPosition({ -650, 900 });
	all_objects.push_back(A3);

	GameObject* A4 = new GameObject();
	A4->SetCollider({ ColliderType::Rect, {0,0,30, 750} });
	A4->SetSize({ 30,750 });
	A4->SetPosition({ -500,-525 });
	all_objects.push_back(A4);

	GameObject* A5 = new GameObject();
	A5->SetCollider({ ColliderType::Rect, {0,0,30, 750} });
	A5->SetSize({ 30,750 });
	A5->SetPosition({ -500,525 });
	all_objects.push_back(A5);

	GameObject* B1 = new GameObject();
	B1->SetCollider({ ColliderType::Rect, {0,0,1500, 30} });
	B1->SetSize({ 1500,30 });
	B1->SetPosition({ 250,150 });
	all_objects.push_back(B1);

	GameObject* B2 = new GameObject();
	B2->SetCollider({ ColliderType::Rect, {0,0,800, 30} });
	B2->SetSize({ 800,30 });
	B2->SetPosition({ -100,-150 });
	all_objects.push_back(B2);

	GameObject* B3 = new GameObject();
	B3->SetCollider({ ColliderType::Rect, {0,0,30, 750} });
	B3->SetSize({ 30,750 });
	B3->SetPosition({ 300,-525 });
	all_objects.push_back(B3);

	/*GameObject* B4 = new GameObject();
	B4->SetCollider({ ColliderType::Rect, {0,0,30, 750} });
	B4->SetSize({ 30,750 });
	B4->SetPosition({ 300,-525 });
	all_objects.push_back(B4);*/
}
