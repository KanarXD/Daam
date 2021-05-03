#pragma once
#include "Renderer/Camera.h"
#include "Components/Transform.h"
#include "Components/RigidBody.h"

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

	static const StateParams walkParams, sprintParams, crouchParams;
	static StateParams activeParams;

	static Player* instance;

	static Transform transform;
	static RigidBody rigidbody;

	static State state;
	
	static Camera camera;

public:
	static void Init(Transform startingTransform = Transform());
	static Player* GetInstance() { return instance; }
	static void Update(float dt);
	static void Destroy();

	static void SetState(State newState);

	static void SetAngularVelocity(bool going, int x, int y);
	static void SetVelocity(bool going, int x, int z);

	static void Jump();

	static void LookAt(glm::vec3 front);

	static const Camera& GetCamera() { return camera; }
	static const Transform& GetTransform() { return transform; }

private:
	Player(Transform startingTransform);

	static void UpdateVelocity();
};
