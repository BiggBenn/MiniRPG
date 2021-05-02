#include "GameObject.hpp"


GameObject::GameObject()
{
	texture = AssetManager::GetAssetManager()->RequestTexture(texturePath);
	sourceRect.width = texture.width;
	sourceRect.height = texture.height;
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
	//update the destination rectangle
	destRect.x = position.x;
	destRect.y = position.y;
	destRect.width = size.x;
	destRect.height = size.y;

	DrawTexturePro(texture, sourceRect, destRect, { destRect.width / 2, destRect.height / 2 }, rotation, WHITE);
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

Vector2 GameObject::GetSize()
{
	return size;
}

void GameObject::SetSize(Vector2 dimensions)
{
	size = dimensions;
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

	//adjust the source rect
	//this would be a good spot to extend the whole thing if you want to add animation, choosing source rect from animation frames
	sourceRect.x = 0;
	sourceRect.y = 0;
	sourceRect.width = texture.width;
	sourceRect.height = texture.height;
}

bool GameObject::CheckFlags(uint8_t flags)
{
	return typeFlags & flags;
}

Collider GameObject::GetCollider()
{
	return collider;
}

void GameObject::SetCollider(Collider coll)
{
	collider = coll;
	if (collider.type != ColliderType::None)
	{
		typeFlags |= TypeFlag::Collision;
	}
}
