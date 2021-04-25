#pragma once
#ifndef SCENE_HPP
#define SCENE_HPP

//system libs
#include <vector>

//other libs

//project includes
#include "GameObject.hpp"

class Scene
{
protected:

	//vector containing all the objects of the scene
	std::vector<GameObject*> all_objects;

	//Raylib camera
	Camera2D camera = { 0 };

public:

	//constructor
	Scene();

	//destructor
	~Scene();

	//initializer intended for children to overwrite
	virtual void Initialize();

	//update all objects
	void update(float delta);

	//draw all of the objects
	void draw();
};

#endif