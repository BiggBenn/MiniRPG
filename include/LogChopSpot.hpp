#pragma once

#ifndef LOGCHOPSPOT_HPP
#define LOGCHOPSPOT_HPP

#include <vector>

#include "InteractableObject.hpp"
#include "TimingGameScene.hpp"
#include "StoryProgress.hpp"

class LogChopSpot : public InteractableObject
{
private:
	//how many logs are still left next to the spot
	int logsLeft;

	//how many logs were chopped already
	int logsChopped = 0;

	//unchopped and chopped logs respectively, with a vector describing the general offset from the center of chop spot
	Vector2 unchoppedOffset = { -75, 0 };
	GameObject* unchoppedLogs;
	GameObject* logStorage;

	Vector2 choppedOffset = { 75, 0 };
	GameObject* choppedLogs;
	GameObject* fireWoodStorage;
public:
	//con- and destructor
	LogChopSpot();
	~LogChopSpot();

	//
	void interact(Player* player);

	//callback functions for the minigame to take in
	void chop();
	void miss();

	//Override from gameobject
	void draw() override;

};

#endif