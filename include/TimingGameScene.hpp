#pragma once

#ifndef TIMINGGAMESCENE_HPP
#define TIMINGGAMESCENE_HPP

#include "MiniGameScene.hpp"

class TimingGameScene : public MiniGameScene
{
private:
	//higher difficulty reduces the size of the target and increases speed of the marker
	float difficulty = 1;
	//marker position goes from -1 (left) to 1 (right)
	float markerPos = 0;
	bool goingRight = true;

	//target size and marker speed calculated depending on difficulty
	float targetSize;
	float targetSizeHalf;
	float markerSpeed;

	//default target size and marker speed
	float defaultTargetSize = 0.3;
	float defaultMarkerSpeed = 2;

	//grace value, if you are off by this percentage, itll still count. The player would prefer to catch a break when they don't deserve it rather than fail when they didn't do anything wrong
	float graceValue = 0.05;

	//The background bar
	GameObject* bar = nullptr;

	//The target
	GameObject* target = nullptr;

	//the marker
	GameObject* marker = nullptr;

public:
	//constructor
	TimingGameScene(std::function<void(void)> success_callback, std::function<void(void)> failure_callback, float Difficulty = 1);

	//Overrides all the way from Scene
	void Initialize() override;
	void update(float delta) override;
	void draw() override;
};

#endif