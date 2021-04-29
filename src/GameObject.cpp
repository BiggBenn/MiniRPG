#include "GameObject.hpp"


GameObject::GameObject(ColliderType collisionType)
{
	collider.type = collisionType;

	texture = AssetManager::GetAssetManager()->RequestTexture(texturePath);
}

GameObject::~GameObject()
{
	//unregister from the texture this object is using
	AssetManager::GetAssetManager()->UnregisterTexture(texturePath);
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

void GameObject::ChangeTexture(std::string path)
{
	//get a handle on the asset manager
	AssetManager* assman = AssetManager::GetAssetManager();

	//unregister old texture
	assman->UnregisterTexture(texturePath);

	//set the new texture
	texturePath = path;
	texture = assman->RequestTexture(texturePath);
}