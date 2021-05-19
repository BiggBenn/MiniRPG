#pragma once

#ifndef INTERACTABLEOBJECT_HPP
#define INTERACTABLEOBJECT_HPP

#include "GameObject.hpp"
#include "Player.hpp"

class InteractableObject : public GameObject
{
protected:

public:
	virtual void interact(Player* player) = 0;
};

#endif