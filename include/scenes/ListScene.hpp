#pragma once
#ifndef LISTSCENE_HPP
#define LISTSCENE_HPP

#include "Scene.hpp"
#include "DialogueScene.hpp"

class ListScene : public Scene
{
private:
	int selected = 0;
	GameObject* selector;
	GameObject* names[11];
	DialogueExecutor* beenThere;
	DialogueExecutor* notYet;
	DialogueExecutor* notImplementedYet;
	DialogueExecutor* jenkinsFirst;

	void adjustSelector();
public:
	void Initialize();

	void update(float delta) override;
};

#endif