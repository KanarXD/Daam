#pragma once
#include "../GameObject.h"

class Bullet : public GameObject
{
protected:
	bool isHit{ false };
	RigidBody rigidbody;

public:
	Bullet(const Transform& transform, const std::string& type = "bullet");
	virtual void Update(float dt) override;
	
	bool IsHit() const { return isHit; }

	virtual void Collision(const GameObject& collidedObject) override;
};

