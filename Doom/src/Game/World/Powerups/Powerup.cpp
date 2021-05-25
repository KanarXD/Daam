#include "pch.h"
#include "Powerup.h"

Powerup::Powerup(const Transform& transform, const std::string& type)
	: GameObject(transform, type) {}

void Powerup::Update(float dt)
{
	GameObject::Update(dt);
	transform.position.y += sin(timer * 3) / 60.0f;
	transform.rotation.y += dt * 3;
	if (!isShown && timer >= timeFromLastPickup + timeBetweenPickups)  isShown = true;
}

void Powerup::Draw()
{
	if (isShown) GameObject::Draw();
}

void Powerup::Collision(const std::string& collidedObjectType)
{
	if (collidedObjectType == "player")
	{
		timeFromLastPickup = timer;
		isShown = false;
	}
}
