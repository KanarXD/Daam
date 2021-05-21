#pragma once
#include "EnemySpecs.h"
#include "Game/Components/Combat.h"
#include "Game/Components/Hitbox.h"
#include "Game/Components/RigidBody.h"
#include "Game/Components/Transform.h"

class Enemy
{
public:
	struct Specs
	{
		Combat combat;
		Hitbox hitbox;
		std::string modelPath;
		float fov;
		float viewDist;
		float speed;
		
		Specs(const Combat& combat, const Hitbox& hitbox, const std::string& modelPath, float fov, float viewDist, float speed);

	};

protected:
	static Specs defualtSpecs;

	RigidBody rigidbody;
	Transform transform;
	Specs activeSpecs;
	
	float timer;

public:
	Enemy(const Transform& transform);
	virtual void Update(float dt);

	bool PlayerInBound() const;

	Transform& GetTransform() { return transform; }
	RigidBody& GetRigidBody() { return rigidbody; }
	Specs& GetSpecs() { return activeSpecs; }

	glm::mat4 GetM() const;
};

