#include "pch.h"
#include "Bullet.h"
#include "../Player.h"

Bullet::Bullet(const Transform& transform, const std::string& type)
	: GameObject(transform, type), rigidbody(RigidBody(glm::vec3(0), glm::vec3(0,0,60))) {}

void Bullet::Update(float dt)
{
	transform.Update(rigidbody, dt);
}


void Bullet::Collision(const GameObject& collidedObject)
{
	isHit = true;
}
