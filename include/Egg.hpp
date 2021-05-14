#pragma once

#include "InteractableObject.hpp"
#include "StoryProgress.hpp"

class Egg : public InteractableObject
{
public:
	//constructor + destructor
	Egg();
	~Egg();

	void interact() override;
};

