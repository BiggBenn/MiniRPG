#include "Weed.hpp"


Weed::Weed()
{
	//tag as interactable
	typeFlags |= TypeFlag::Interactable;
}

Weed::~Weed()
{

}

void Weed::interact()
{
	//prepare function to hand over to the button mash scene
	std::function<void(void)> success_callback = std::bind(&Weed::pullOut, this);
	//create button mash scene with pullOut as the callback on success
	//set the difficulty randomly between 0.85 and 1.15
	Scene* miniGameScene = new ButtonMashScene(success_callback, nullptr, (float) GetRandomValue(85, 115) / 100.0f);
	SceneManager::GetSceneManager()->AddScene(miniGameScene);
}

void Weed::pullOut()
{
	//increment how many weeds were plucked, and mark this weed for deletion
	StoryProgress::weedsPlucked++;
	DeleteFlag = true;
}