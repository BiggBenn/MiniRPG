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

	//handle collisions, after the fact because the player is not going to move all that much. Higher speed situations would do better with projecting the planned movement ahead, and cutting it short to not collide
	handleCollisions();

	//Interaction
	if (IsKeyPressed(KEY_SPACE))
	{
		interact();
	}

	parentScene->updatePlayerCoordinates(this->GetPosition());
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
			iobj->interact(this);

			//return to make sure the player only interacts with a single object per button press
			return;
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
		return CtoCCollision(differenceVector, collider.radius, otherCollider.radius);
	}
	//circle to rectangle collision
	else if (collider.type == ColliderType::Circle && otherCollider.type == ColliderType::Rect)
	{
		return CtoRCollision(differenceVector, collider.radius, otherCollider.rect);
	}
	//rect to circle collision
	else if (collider.type == ColliderType::Rect && otherCollider.type == ColliderType::Circle)
	{
		//not going to happen since player only has circle collider, otherwise just a reverse copy of the one above
		return result;
	}
	//rect to rect collision
	else if (collider.type == ColliderType::Rect && otherCollider.type == ColliderType::Rect)
	{
		//not going to happen since player only has circle collider
		return result;
	}

	return result;
}

Vector2 Player::CtoCCollision(Vector2 distance, float radius1, float radius2)
{
	//calculate the overlap of the circles
	float overlap = Vector2Length(distance) - radius1 - radius2;
	if (overlap < 0)
	{
		//move the player away by the overlap
		return Vector2Normalize(distance) * overlap;
	}
	return Vector2Zero();
}



Vector2 Player::CtoRCollision(Vector2 distance, float radius, Rectangle rect)
{
	Vector2 result = { 0,0 };

	//circle is above/in/below the middle section of the rectangle
	if (distance.x > -rect.width / 2 && distance.x < rect.width / 2)
	{
		//above center
		if (distance.y > 0)
		{
			//calculate overlap
			float overlap = abs(distance.y) - rect.height / 2 - collider.radius;
			if (overlap < 0)
			{
				//move away from center box in the opposite direction from the approach vector
				result.y = overlap;
			}
		}
		//below center
		else
		{
			float overlap = abs(distance.y) - rect.height / 2 - collider.radius;
			if (overlap < 0)
			{
				result.y = -overlap;
			}
		}
	}
	//circle is left/in/right of the middle section of the rectangle
	else if (distance.y > -rect.height / 2 && distance.y < rect.height / 2)
	{
		//right of center
		if (distance.x < 0)
		{
			float overlap = abs(distance.x) - rect.width / 2 - collider.radius;
			if (overlap < 0)
			{
				result.x = -overlap;
			}
		}
		//left of center
		else
		{
			float overlap = abs(distance.x) - rect.width / 2 - collider.radius;
			if (overlap < 0)
			{
				result.x = overlap;
			}
		}
	}
	//the corner cases
	else
	{
		//set up modifier vector to reach the corners from the center of the rectangle
		Vector2 mod;

		//top corners
		if (distance.y > 0)
		{
			//top left corner
			if (distance.x < 0)
			{
				//The modifier just ensures that distance + mod points from the player coordinates to the coordinates of the *corner* of the rectangle
				mod.x = rect.width / 2;
				mod.y = -rect.height / 2;
				return CtoCCollision(distance + mod, 0, radius);
			}
			//top right corner
			else
			{
				mod.x = -rect.width / 2;
				mod.y = -rect.height / 2;
				return CtoCCollision(distance + mod, 0, radius);
			}
		}
		//bottom corners
		else
		{
			//bottom left corner
			if (distance.x < 0)
			{
				mod.x = rect.width / 2;
				mod.y = rect.height / 2;
				return CtoCCollision(distance + mod, 0, radius);
			}
			//bottom right corner
			else
			{
				mod.x = -rect.width / 2;
				mod.y = rect.height / 2;
				return CtoCCollision(distance + mod, 0, radius);
			}
		}
	}

	return result;
}
