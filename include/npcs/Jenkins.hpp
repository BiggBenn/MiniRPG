#pragma once

#include "InteractableObject.hpp"
#include "DialogueBuilder.hpp"

class Jenkins : public InteractableObject
{
private:
	//different faces for portraits
	Texture2D normal_face;
	Texture2D happy_face;

	DialogueExecutor* first_talk;
	DialogueExecutor* after_talk;

	bool talkedTo = false;
public:
	Jenkins();
	~Jenkins();

	void interact(Player* player) override;
};

