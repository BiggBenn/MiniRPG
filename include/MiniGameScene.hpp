#pragma once

#ifndef MINIGAMESCENE_HPP
#define MINIGAMESCENE_HPP

#include <functional>

#include "Scene.hpp"
#include "SceneManager.hpp"

class MiniGameScene : public Scene
{
protected:
	//Callback functions, called on success or failure of the minigame, respectively
	std::function<void(void)> successCallback = nullptr;
	std::function<void(void)> failureCallback = nullptr;
public:
	//constructor
	MiniGameScene(std::function<void(void)> success_callback, std::function<void(void)> failure_callback);

	//override of Initialize function, called by SceneManager on being added
	void Initialize() override;

	//override of Scene update and draw functions
	void update(float delta) override;
	void draw() override;

	//functions that call the success and failure callbacks
	virtual void success();
	virtual void failure();
};

#endif