#pragma once
#ifndef PLAYER_HPP
#define PLAYER_HPP


#include "GameObject.hpp"
#include "Scene.hpp"
#include "InteractableObject.hpp"

class Player : public GameObject
{
protected:
	//speed player moves at in pixels/second
	float speed = 100;

	//
	float interactionRange = 250;

	//
	float collisionRange = 2000;

	Scene* parentScene;

	//scans for nearby objects, whether they are interactable, and interacts with them
	void interact();

	//finds nearby objects and moves the player out of their colliders.
	void handleCollisions();

	//calculates the correctional movement of a single collision
	Vector2 collide(GameObject* otherObj);
public:

	Player(Scene* owner);

	void update(float delta) override;
};

#endif