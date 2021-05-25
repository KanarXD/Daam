#pragma once
#include "../../../GameObject.h"
#include "../EnemySpecs.h"
#include "Game/Components/Combat.h"
#include "Game/Components/Healthbar.h"
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

	Healthbar healthbar;
	RigidBody rigidbody;
	Specs activeSpecs;
	
public:
	Enemy(const Transform& transform, const std::string& type = "enemy");
	virtual void Update(float dt) override;
	void Draw() override;

	virtual void Collision(const GameObject& collidedObject) override;

	bool PlayerInBound(const glm::vec3& playerPos, float angToPlayer) const;

	RigidBody& GetRigidBody() { return rigidbody; }
	Specs& GetSpecs() { return activeSpecs; }
};

