#pragma once
#include "Renderer/Camera.h"
#include "Components/Combat.h"
#include "Components/Hitbox.h"
#include "Components/Transform.h"
#include "Components/RigidBody.h"
#include "GameObject.h"

class Player
{
public:
	enum class State : int { Walk = 1, Sprint = 2, Crouch = 3 };
	struct StateParams
	{
		float angularVelocity;
		float velocity;
		float height;

		StateParams(float angularVelocity, float velocity, float height)
			: angularVelocity(angularVelocity), velocity(velocity), height(height) {}
	};

private:
	const Player::StateParams walkParams{ 2.0f, 10.0f, 2.0f };
	const Player::StateParams sprintParams{ 2.0f, 20.0f, 2.0f };
	const Player::StateParams crouchParams{ 2.0f, 5.0f, 1.0f };
	StateParams activeParams = walkParams;

	Combat combat = { 1000, 30, 0.1f };
	Hitbox hitbox = GOModels.at("player").hitbox;
	Transform transform;
	RigidBody rigidbody;

	State state = State::Walk;
	Camera camera = Camera(Transform(), 50.0f);

	float timer = 0;
	float lastShootTime = 0;
public:
	static std::shared_ptr<Player> GetInstance();

	void Update(float dt);

	void Collision(GameObject& collidedObject);

	void SetState(State newState);
	void SetTransform(Transform transform = Transform());
	void SetAngularVelocity(bool going, int x, int y);
	void SetVelocity(bool going, int x, int z);

	void Jump();

	void LookAt(glm::vec3 front);
	void Shoot();

	const Camera& GetCamera() { return camera; }

	Combat& GetCombat() { return combat; }
	Hitbox& GetHitbox() { return hitbox; }
	Transform& GetTransform() { return transform; }
	RigidBody& GetRigidBody() { return rigidbody; }

private:
	void UpdateVelocity();
};
