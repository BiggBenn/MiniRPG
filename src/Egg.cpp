#include "Egg.hpp"
#include "StoryProgress.hpp"

Egg::Egg()
{
	//tag this object as interactable
	typeFlags |= TypeFlag::Interactable;

	//Load up the egg texture
	ChangeTexture("resources/egg.png");
}

Egg::~Egg()
{

}

void Egg::interact(Player* player)
{
	StoryProgress::eggsCollected += 1;
	DeleteFlag = true;
}