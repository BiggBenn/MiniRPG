#pragma once
#ifndef EXITPOINT_HPP
#define EXITPOINT_HPP

#include "InteractableObject.hpp"
#include "DialogueExecutor.hpp"

class ExitPoint : public InteractableObject
{
private:
	DialogueExecutor* confirmationDialogue;
	bool reallyLeave = false;

public:
	ExitPoint();
	~ExitPoint();

	void interact(Player* player) override;

	void update(float delta) override;
};

#endif