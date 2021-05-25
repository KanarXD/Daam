#pragma once
#include "../../GameObject.h"
#include "Game/Components/RigidBody.h"

class Powerup : public GameObject
{
protected:
	bool isShown{ true };
	const float timeBetweenPickups{ 10.0f };
	float timeFromLastPickup{ 0.0f };

public:
	Powerup(const Transform& transform, const std::string& type = "default");
	virtual void Update(float dt) override;
	virtual void Draw() override;

	virtual void Collision(const std::string& collidedObjectType) override;
};

