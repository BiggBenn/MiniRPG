#pragma once

//forward decl
//class GameObject;

#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

//system libs
#include <string>

//other libs
#include "raylib.h"
#include "raymath.h"

//project includes
#include "AssetManager.hpp"	
#include "TypeFlags.hpp"

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
	//type of this object, so other objects can more easily identify them from just a GameObject* pointer
	uint8_t typeFlags = 0b00000000;

	//
	Vector2 position = { 0,0 };

	//
	Vector2 velocity = { 0,0 };

	//Z value is depth in image, flag is triggered on change of z, so we can sort after update.
	int z = 0;
	

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
	GameObject(std::string texPath = "resources/defaultTexture.png");

	//destructor
	virtual ~GameObject();

	//update function, delta is time passed since last frame
	virtual void update(float delta);

	//drawing function
	virtual void draw();

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

	//checks whether this object has the flags requested
	bool CheckFlags(uint8_t flags);
	void AddFlags(uint8_t flags);
	void RemoveFlags(uint8_t flags);

	//Getset for collider
	Collider GetCollider();
	void SetCollider(Collider coll);

	//Getset for rotation
	float GetRotation();
	void SetRotation(float rot);

	//getset for z
	int GetZ();
	void SetZ(int value);

	//Delete flag, if true the object will be deleted after the update cycle
	bool DeleteFlag = false;

	//flag that indicates whether or not z was changed, so the object vector can be sorted
	bool zChanged = false;


	static bool CompareZ(GameObject* A, GameObject* B);
};

#endif