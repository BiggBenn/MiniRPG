#pragma once

#ifndef SCENEMANAGER_HPP
#define SCENEMANAGER_HPP

#include <vector>

#include "Scene.hpp"


//Basically just a stack of scenes, pop and add scenes
class SceneManager
{
private:
	std::vector<Scene*> scenes;
	std::vector<Scene*> pendingDelete;
	
	//
	static SceneManager* Singleton;

	//constructor
	SceneManager();

public:
	//
	static SceneManager* GetSceneManager();

	//adds a scene to the top of the stack
	void AddScene(Scene* scene);

	//pops the topmost scene
	void PopScene();

	//updates only the topmost scene
	void update(float delta);

	//draws all scenes sequentially
	void draw();
};

#endif