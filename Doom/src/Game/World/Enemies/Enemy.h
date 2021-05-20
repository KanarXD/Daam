#pragma once
#include "EnemySpecs.h"
#include "Game/Components/RigidBody.h"
#include "Game/Components/Transform.h"

class Enemy
{
public:
	enum class Type : int { ET1 = 1, ET2 = 2, ET3 = 3 };

private:
	Type type;
	RigidBody rigidbody;
	Transform transform;

	const EnemySpecs* specs;
	float health;
	
public:
	Enemy(Type type, const EnemySpecs* specs, const Transform& transform, float health);

	bool PlayerInBound() const;

	Type GetEnemyType() const { return type; }
	Transform& GetTransform() { return transform; }
	RigidBody& GetRigidBody() { return rigidbody; }

	const EnemySpecs* GetSpecs() const { return specs; }
	float GetHealth() const { return health; }

	const glm::mat4 &GetM() const;
};

