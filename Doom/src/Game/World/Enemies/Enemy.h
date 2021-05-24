#pragma once
#include "../../GameObject.h"
#include "EnemySpecs.h"
#include "Game/Components/Combat.h"
#include "Game/Components/RigidBody.h"

class Enemy : public GameObject
{
public:
	struct Specs
	{
		Combat combat;
		float fov;
		float viewDist;
		float speed;
		
		Specs(const Combat& combat, float fov, float viewDist, float speed);
	};

protected:
	static Specs defualtSpecs;

	RigidBody rigidbody;
	Specs activeSpecs;
	
public:
	Enemy(const Transform& transform, const std::string& type = "enemy");
	virtual void Update(float dt) override;

	virtual void Collision(const GameObject& collidedObject) override;

	bool PlayerInBound() const;

	RigidBody& GetRigidBody() { return rigidbody; }
	Specs& GetSpecs() { return activeSpecs; }
};

