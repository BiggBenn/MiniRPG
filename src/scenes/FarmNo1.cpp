#include "scenes/FarmNo1.hpp"

#include "ExitPoint.hpp"
#include "StoryProgress.hpp"

void FarmNo1::Initialize()
{
	//Spawn background image
	GameObject* background = new GameObject();
	background->ChangeTexture("resources/maps/farm_jenkins/map.png");
	background->SetZ(-50);
	background->SetSize({ 3000, 3000});
	background->SetPosition({ 150, -100 });
	all_objects.push_back(background);

	//spawn barn
	GameObject* barn = new GameObject();
	barn->ChangeTexture("resources/maps/farm_jenkins/barn.png");
	barn->SetZ(15);
	barn->SetSize({ 750,750 });
	barn->SetPosition({ -100,-500 });
	all_objects.push_back(barn);

	//spawn house
	GameObject* house = new GameObject();
	house->ChangeTexture("resources/maps/farm_jenkins/house.png");
	house->SetZ(15);
	house->SetSize({ 800,600 });
	house->SetPosition({ 925,-675 });
	all_objects.push_back(house);

	//spawn tractor
	GameObject* tractor = new GameObject();
	tractor->ChangeTexture("resources/maps/farm_jenkins/tractor.png");
	tractor->SetZ(15);
	tractor->SetSize({ 200,400 });
	tractor->SetPosition({ 1000, -100 });
	all_objects.push_back(tractor);

	
	//note that the player visited jenkins already
	StoryProgress::farmsVisited[0] = true;

	//spawn jenkins somewhere
	Jenkins* jenkins = new Jenkins();
	jenkins->SetPosition({ 650,125 });
	all_objects.push_back(jenkins);

	//spawn the player
	Player* player = new Player(this);
	player->SetZ(50);
	all_objects.push_back(player);

	bool hideMechanical = false;

	//spawn exit point
	ExitPoint* point = new ExitPoint();
	all_objects.push_back(point);
	point->SetPosition({ -650, 800 });
	if (hideMechanical)
		point->AddFlags(TypeFlag::Invisible);

	//spawn exit point
	ExitPoint* point2 = new ExitPoint();
	all_objects.push_back(point2);
	point2->SetPosition({ -650, -800 });
	if (hideMechanical)
		point2->AddFlags(TypeFlag::Invisible);

	//create colliders
	GameObject* A1 = new GameObject();
	A1->SetCollider({ ColliderType::Rect, {0,0,30, 1800} });
	A1->SetSize({ 30,1800 });
	A1->SetPosition({ -800,0 });
	A1->SetZ(999);
	all_objects.push_back(A1);
	if (hideMechanical)
		A1->AddFlags(TypeFlag::Invisible);

	GameObject* A2 = new GameObject();
	A2->SetCollider({ ColliderType::Rect, {0,0,300, 30} });
	A2->SetSize({ 300, 30 });
	A2->SetPosition({ -650, -900 });
	A2->SetZ(999);
	all_objects.push_back(A2);
	if (hideMechanical)
		A2->AddFlags(TypeFlag::Invisible);

	GameObject* A3 = new GameObject();
	A3->SetCollider({ ColliderType::Rect, {0,0,300, 30} });
	A3->SetSize({ 300, 30 });
	A3->SetPosition({ -650, 900 });
	A3->SetZ(999);
	all_objects.push_back(A3);
	if (hideMechanical)
		A3->AddFlags(TypeFlag::Invisible);

	GameObject* A4 = new GameObject();
	A4->SetCollider({ ColliderType::Rect, {0,0,30, 750} });
	A4->SetSize({ 30,750 });
	A4->SetPosition({ -500,-525 });
	A4->SetZ(999);
	all_objects.push_back(A4);
	if (hideMechanical)
		A4->AddFlags(TypeFlag::Invisible);

	GameObject* A5 = new GameObject();
	A5->SetCollider({ ColliderType::Rect, {0,0,30, 750} });
	A5->SetSize({ 30,750 });
	A5->SetPosition({ -500,525 });
	A5->SetZ(999);
	all_objects.push_back(A5);
	if (hideMechanical)
		A5->AddFlags(TypeFlag::Invisible);

	GameObject* B1 = new GameObject();
	B1->SetCollider({ ColliderType::Rect, {0,0,1500, 30} });
	B1->SetSize({ 1500,30 });
	B1->SetPosition({ 250,150 });
	B1->SetZ(999);
	all_objects.push_back(B1);
	if (hideMechanical)
		B1->AddFlags(TypeFlag::Invisible);

	GameObject* B2 = new GameObject();
	B2->SetCollider({ ColliderType::Rect, {0,0,800, 30} });
	B2->SetSize({ 800,30 });
	B2->SetPosition({ -100,-150 });
	B2->SetZ(999);
	all_objects.push_back(B2);
	if (hideMechanical)
		B2->AddFlags(TypeFlag::Invisible);

	GameObject* B3 = new GameObject();
	B3->SetCollider({ ColliderType::Rect, {0,0,30, 550} });
	B3->SetSize({ 30,550 });
	B3->SetPosition({ 300,-425 });
	B3->SetZ(999);
	all_objects.push_back(B3);
	if (hideMechanical)
		B3->AddFlags(TypeFlag::Invisible);

	GameObject* B4 = new GameObject();
	B4->SetCollider({ ColliderType::Rect, {0,0,250, 30} });
	B4->SetSize({ 250,30 });
	B4->SetPosition({ 425,-700 });
	B4->SetZ(999);
	all_objects.push_back(B4);
	if (hideMechanical)
		B4->AddFlags(TypeFlag::Invisible);

	GameObject* B5 = new GameObject();
	B5->SetCollider({ ColliderType::Rect, {0,0,30, 325} });
	B5->SetSize({ 30,325 });
	B5->SetPosition({ 550,-550 });
	B5->SetZ(999);
	all_objects.push_back(B5);
	if (hideMechanical)
		B5->AddFlags(TypeFlag::Invisible);

	GameObject* B6 = new GameObject();
	B6->SetCollider({ ColliderType::Rect, {0,0,400, 30} });
	B6->SetSize({ 400,30 });
	B6->SetPosition({ 750,-400 });
	B6->SetZ(999);
	all_objects.push_back(B6);
	if (hideMechanical)
		B6->AddFlags(TypeFlag::Invisible);

	GameObject* B7 = new GameObject();
	B7->SetCollider({ ColliderType::Rect, {0,0,30, 550} });
	B7->SetSize({ 30,550 });
	B7->SetPosition({ 925,-125 });
	B7->SetZ(999);
	all_objects.push_back(B7);
	if (hideMechanical)
		B7->AddFlags(TypeFlag::Invisible);
}
