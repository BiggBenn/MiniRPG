#pragma once

#ifndef EGG_HPP
#define EGG_HPP

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

#endif