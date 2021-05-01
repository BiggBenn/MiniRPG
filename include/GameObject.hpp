#pragma once
#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

//system libs
#include <string>

//other libs
#include "raylib.h"
#include "raymath.h"

//project includes
#include "AssetManager.hpp"

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

	//texture*path* of the object
	std::string texturePath = "resources/defaultTexture.png";

	//texture of object
	Texture2D texture = { 0 };

	//source and destination rectangle for drawing
	Rectangle sourceRect = { 0 };
	Rectangle destRect = { 0 };

	//rotation of the object, applied to the texture; 0 is pointing UP, 0 <= rot < 360
	float rotation = 0;

	//size of the object
	Vector2 size = { 100,100 };

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

	//getset for size
	Vector2 GetSize();
	void SetSize(Vector2 dimensions);

	//both unregisters old texture and requests new one
	void ChangeTexture(std::string path);
};

#endif