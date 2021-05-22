#ifndef TESTNPC_H
#define TESTNPC_H
#pragma once

#include "InteractableObject.hpp"
#include "DialogueBuilder.hpp"
	
class TestNpc : public InteractableObject
{
	private:
		Texture2D			normal_face;
		DialogueBuilder*	db;
		DialogueExecutor* 	dialogue_current;
		DialogueExecutor* 	dialogue_start;
		DialogueExecutor* 	dialogue_in_progress;
		DialogueExecutor* 	dialogue_finished;

		bool 				acceptedQuest = false;

	public:

		TestNpc();
		~TestNpc();

		//interact override
		void interact(Player* player) override;

};
#endif