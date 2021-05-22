#include "pch.h"
#include "Powerup.h"

Powerup::Powerup(const RigidBody& rigidbody, const Transform& transform, float timeBetweenPickups)
	: GameObject(transform, "default"), rigidbody(rigidbody), timeBetweenPickups(timeBetweenPickups) {}

void Powerup::Update(float dt)
{
}

void Powerup::Draw()
{
}

void Powerup::Collision(const GameObject& collidedObject)
{
}
