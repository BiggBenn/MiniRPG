#pragma once
#ifndef INTROSCENE_HPP
#define INTROSCENE_HPP

#include "Scene.hpp"
#include "DialogueScene.hpp"

class IntroScene : public Scene
{
private:
	DialogueExecutor* dialogue;
	DialogueExecutor* goToJenkins;
	Texture2D marv_normal;
	Texture2D marv_happy;
	GameObject* background;
	bool introDialogueDone = false;

	void SwitchBackground();
public:
	~IntroScene();
	void Initialize() override;

	void update(float delta) override;
};

#endif