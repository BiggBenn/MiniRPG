#include "GameObject.hpp"


GameObject::GameObject(ColliderType collisionType)
{

}

GameObject::~GameObject()
{

}

void GameObject::update(float delta)
{
	position = position + velocity * delta;
}

void GameObject::draw()
{
	DrawTextureEx(texture, position, rotation, scale, WHITE);
}

Vector2 GameObject::GetPosition()
{
	return position;
}

void GameObject::SetPosition(Vector2 pos)
{
	position = pos;
}

Vector2 GameObject::GetVelocity()
{
	return velocity;
}

void GameObject::SetVelocity(Vector2 vel)
{
	velocity = vel;
}