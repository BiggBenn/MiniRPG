#pragma once

#ifndef WEED_HPP
#define WEED_HPP

#include "InteractableObject.hpp"
#include "SceneManager.hpp"
#include "StoryProgress.hpp"
#include "ButtonMashScene.hpp"

class Weed : public InteractableObject
{
public:
	//de- and constructor
	Weed();
	~Weed();

	//interact override
	void interact(Player* player) override;

	//callback thatll pull out the weed
	void pullOut();
};

#endif