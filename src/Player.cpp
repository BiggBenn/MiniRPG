#include "Player.hpp"


Player::Player(Scene* owner) : GameObject()
{
	parentScene = owner;
	ChangeTexture("resources/player.png");
	size = { 128,128 };
	collider.type = ColliderType::Circle;
	collider.radius = 64;
}

void Player::update(float delta)
{
	//Movement
	Vector2 direction = { 0,0 };
	if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
	{
		direction = direction + Vector2Left();
	}
	if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
	{
		direction = direction + Vector2Right();
	}
	if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))
	{
		direction = direction + Vector2Up();
	}
	if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))
	{
		direction = direction + Vector2Down();
	}

	if (direction != Vector2Zero())
	{
		direction = Vector2Normalize(direction);
		position = position + direction * speed * delta;
		rotation = Vector2Angle(Vector2Up(), direction);
	}

	//handle collisions, after the fact because the player is not going to move aall that much. Higher speed situations would do better with projecting the planned movement ahead, and cutting it short to not collide
	handleCollisions();

	//Interaction
	if (IsKeyDown(KEY_SPACE))
	{
		interact();
	}

}

void Player::interact()
{
	//first check what objects are "nearby", if perf is slow, keep the vector loaded instead of creating and destroying
	std::vector<GameObject*> nearbyObjects;
	parentScene->GetNearbyObjects(position, interactionRange, &nearbyObjects);

	//iterate through all these nearby objects
	for (GameObject* gobj : nearbyObjects) 
	{
		if (gobj->CheckFlags(TypeFlag::Interactable) && gobj != this)
		{
			InteractableObject* iobj = (InteractableObject*)gobj;
			iobj->interact();
		}
	}
}

void Player::handleCollisions()
{
	Vector2 correctiveMovement = { 0,0 };
	std::vector <GameObject*> nearbyObjects;
	parentScene->GetNearbyObjects(position, collisionRange, &nearbyObjects);

	for (GameObject* gobj : nearbyObjects)
	{
		if (gobj->CheckFlags(TypeFlag::Collision) && gobj != this)
		{
			correctiveMovement = correctiveMovement + collide(gobj);
		}
	}

	position = position + correctiveMovement;
}

Vector2 Player::collide(GameObject* otherObj)
{
	//set up result variable
	Vector2 result = Vector2Zero();
	
	//load up commonly used infos
	Vector2 differenceVector = otherObj->GetPosition() - position;
	float distance = Vector2Length(differenceVector);
	Collider otherCollider = otherObj->GetCollider();

	//if either doesnt have any collision (why was the flag set as that then?) just return the zero vector
	if (collider.type == ColliderType::None || otherCollider.type == ColliderType::None)
		return result;

	//Circle to circle collision
	if (collider.type == ColliderType::Circle && otherCollider.type == ColliderType::Circle)
	{
		//calculate the overlap of the circles
		float overlap = distance - collider.radius - otherCollider.radius; 
		if (overlap < 0)
		{
			//move the player away by the overlap
			result = Vector2Normalize(differenceVector) * overlap;
		}
		return result;
	}
	//circle to rectangle collision
	else if (collider.type == ColliderType::Circle && otherCollider.type == ColliderType::Rect)
	{
		
	}
	//rect to circle collision
	else if (collider.type == ColliderType::Rect && otherCollider.type == ColliderType::Circle)
	{

	}
	//rect to rect collision
	else if (collider.type == ColliderType::Rect && otherCollider.type == ColliderType::Rect)
	{

	}

}