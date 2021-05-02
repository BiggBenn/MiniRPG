#pragma once

//forward declaration
class Scene;

#ifndef SCENE_HPP
#define SCENE_HPP

//system libs
#include <vector>

//other libs

//project includes
#include "GameObject.hpp"
#include "Player.hpp"

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

	//returns objects who's position is within range of the given coordinates
	//if this is slow, implement SQS system from your other repo, but since this small game won't have more than a hundred or so objects and only the player will really ask for nearby objects, naive should be ok
	void GetNearbyObjects(Vector2 coordinates, float range, std::vector<GameObject*>* outputVector);
};

#endif