#pragma once
#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

//system libs

//other libs
#include "raylib.h"
#include "raymath.h"

//project includes


enum ColliderType
{
	None = 0,
	Rect,
	Circle
};

struct Collider
{
	ColliderType type;
	Rectangle rect;	//in case of rectangle type, use this
	float radius;	//in case of circle collider type use this
};

class GameObject
{
protected:

	//
	Vector2 position = { 0,0 };

	//
	Vector2 velocity = { 0,0 };

	//texture of object
	Texture2D texture = { 0 };

	//rotation of the object, applied to the texture; 0 is pointing UP, 0 <= rot < 360
	float rotation = 0;

	//scale of the object
	float scale = 1;

	//collider of this object
	Collider collider = { None };


public:

	//constructor
	GameObject(ColliderType collisionType);

	//destructor
	~GameObject();

	//update function, delta is time passed since last frame
	void update(float delta);

	//drawing function
	void draw();

	//getset for position
	Vector2 GetPosition();
	void SetPosition(Vector2 pos);

	//getset for velocity
	Vector2 GetVelocity();
	void SetVelocity(Vector2 vel);


};

#endif