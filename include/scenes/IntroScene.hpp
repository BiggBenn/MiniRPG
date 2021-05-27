#pragma once
#ifndef INTROSCENE_HPP
#define INTROSCENE_HPP

#include "Scene.hpp"
#include "DialogueScene.hpp"

class IntroScene : public Scene
{
private:
	DialogueExecutor* dialogue;
	Texture2D marv_normal;
	Texture2D marv_happy;
	bool introDialogueDone = false;

public:
	~IntroScene();
	void Initialize() override;

	void update(float delta) override;
};

#endif