#pragma once
#include "../../GameObject.h"
#include "Game/Components/RigidBody.h"

class Powerup : public GameObject
{
protected:
	RigidBody rigidbody;
	bool isShown{ true };
	float timeBetweenPickups;

public:
	Powerup(const RigidBody& rigidbody, const Transform& transform, float timeBetweenPickups);
	virtual void Update(float dt) override;
	void Draw() override;

	virtual void Collision(const GameObject& collidedObject) override;
};

