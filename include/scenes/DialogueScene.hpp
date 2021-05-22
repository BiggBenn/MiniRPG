#ifndef DIALOGUESCENE_H
#define DIALOGUESCENE_H
#pragma once

#include "Scene.hpp"
#include "SceneManager.hpp"
#include "DialogueExecutor.hpp"
	
class DialogueScene : public Scene
{
	private:
		DialogueExecutor* 	executor;

	public:

		DialogueScene(DialogueExecutor* executor);
		~DialogueScene();

		//override of Initialize function, called by SceneManager on being added
		void Initialize() override;

		//override of Scene update and draw functions
		void update(float delta) override;
		void draw() override;

};

#endif