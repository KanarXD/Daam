#include "pch.h"
#include "Player.h"

Player* Player::instance = nullptr;

const Player::StateParams Player::walkParams{ 2.0f, 10.0f, 2.0f };
const Player::StateParams Player::sprintParams{ 2.0f, 20.0f, 2.0f };
const Player::StateParams Player::crouchParams{ 2.0f, 5.0f, 1.0f };

Player::StateParams Player::activeParams = Player::walkParams;

Combat Player::combat{};
Transform Player::transform{};
RigidBody Player::rigidbody{};

Player::State Player::state = Player::State::Walk;

Camera Player::camera = Camera(Transform(), 50.0f);

void Player::Init(Transform startingTransform)
{
	if (instance == nullptr) instance = new Player(startingTransform);
}

void Player::Update(float dt)
{
	if (transform.position.y > 0)
		rigidbody.velocity.y -= 2 * Consts::G * dt;
	else if (transform.position.y < 0)
	{
		transform.position.y = 0.0f;
		rigidbody.velocity.y = 0.0f;
	}

	transform.Update(rigidbody, dt);
	camera.SetTransform(transform, activeParams.height);
}

void Player::Destroy()
{
	delete instance;
}

void Player::SetState(State newState)
{
	state = newState;

	switch (state)
	{
	case Player::State::Walk:  activeParams = walkParams;	break;
	case Player::State::Sprint:   activeParams = sprintParams;	break;
	case Player::State::Crouch: activeParams = crouchParams;	break;
	}

	UpdateVelocity();
}

void Player::SetAngularVelocity(bool going, int x, int y)
{
	rigidbody.angularVelocity.x = (x) ? x * activeParams.angularVelocity * going : rigidbody.angularVelocity.x;
	rigidbody.angularVelocity.y = (y) ? y * activeParams.angularVelocity * going : rigidbody.angularVelocity.y;
}

void Player::SetVelocity(bool going, int x, int z)
{
	rigidbody.velocity.x = (x)? x * activeParams.velocity * going : rigidbody.velocity.x;
	rigidbody.velocity.z = (z)? z * activeParams.velocity * going : rigidbody.velocity.z;
}

void Player::Jump()
{
	if (transform.position.y) return;
	rigidbody.velocity.y = 10.0f;
}

void Player::LookAt(glm::vec3 front)
{
	// transform.rotation.x = atan2(front.z, front.y);
	transform.rotation.y = atan2(front.x, front.z);
	// transform.rotation.z = atan2(front.y, front.x);
}

Player::Player(Transform startingTransform)
{
	camera = Camera(startingTransform, 50.0f);
	transform = startingTransform;
}

void Player::UpdateVelocity()
{
	rigidbody.velocity.x = glm::sign(rigidbody.velocity.x) * activeParams.velocity;
	rigidbody.velocity.z = glm::sign(rigidbody.velocity.z) * activeParams.velocity;
}