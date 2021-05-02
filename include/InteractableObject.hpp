#pragma once

#ifndef INTERACTABLEOBJECT_HPP
#define INTERACTABLEOBJECT_HPP

#include "GameObject.hpp"

class InteractableObject : public GameObject
{
protected:

public:
	InteractableObject();

	virtual void interact();
};

#endif