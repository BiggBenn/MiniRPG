#pragma once

#ifndef BUTTONMASHSCENE_HPP
#define BUTTONMASHSCENE_HPP

#include "MiniGameScene.hpp"

class ButtonMashScene : public MiniGameScene
{
private:
	//difficulty from 0 to infinity. above a value that I havent calculated, it would be mathematically impossible to win
	float difficulty = 1;
	//the progress towards winning, 1 is victory
	float mashValue = 0;
	
	//how long the mashvalue has been at 0. Once this goes above the timeout value, the minigame is failed
	float failTimer = 0;
	float timeout = 2;	//2 second timeout

	//The shape of the bar in total, the container
	GameObject* barShape;
	//the bar that actually gets longer upon player button mashing
	GameObject* barFilling;
public:
	//constructor
	ButtonMashScene(std::function<void(void)> success_callback, std::function<void(void)> failure_callback, float Difficulty = 1);

	//Overrides all the way from Scene
	void Initialize() override;
	void update(float delta) override;
	void draw() override;
};

#endif