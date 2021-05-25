#include "pch.h"
#include "Player.h"
#include "GameObjectsModels.h"
#include "Renderer/Renderer.h"
#include "Renderer/Library/ModelsLibrary.h"


std::shared_ptr<Player> Player::GetInstance()
{
	static std::shared_ptr<Player> playerInstance(new Player());
	return playerInstance;
}

Player::StateParams Player::activeParams = Player::walkParams;

Combat Player::combat{ 1000, 30, 0.5f };
Hitbox Player::hitbox = GOModels.at("player").hitbox;
Transform Player::transform{};
RigidBody Player::rigidbody{};

Player::State Player::state = Player::State::Walk;

Camera Player::camera = Camera(Transform(), 50.0f);

void Player::Init(Transform startingTransform)
{
	this->transform = transform;
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

void Player::Collision(GameObject& collidedObject)
{
	if (collidedObject.GetType() == "box")
	{
		glm::vec3 boxPos = collidedObject.GetTransform().position + collidedObject.GetHitbox().offset;
		glm::vec3 boxSize = collidedObject.GetTransform().scale * collidedObject.GetHitbox().scaleModifier;
		float distX = transform.position.x + hitbox.offset.x - boxPos.x;
		float distZ = transform.position.z + hitbox.offset.z - boxPos.z;

		if (fabs(distX) > fabs(distZ))
		{
			if (distX < 0)
				transform.position.x = boxPos.x - boxSize.x - transform.scale.x * hitbox.scaleModifier.x - hitbox.offset.x;
			else																						 
				transform.position.x = boxPos.x + boxSize.x + transform.scale.x * hitbox.scaleModifier.x - hitbox.offset.x;
		}																								 
		else
		{
			if (distZ < 0)
				transform.position.z = boxPos.z - boxSize.z - transform.scale.z * hitbox.scaleModifier.z - hitbox.offset.z;
			else
				transform.position.z = boxPos.z + boxSize.z + transform.scale.z * hitbox.scaleModifier.z - hitbox.offset.z;
		}
	}
	else if (collidedObject.GetType() == "healthkit")
	{
		combat.health += 100;
		if (combat.health > combat.maxHealth) combat.health = combat.maxHealth;
	}
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

void Player::UpdateVelocity()
{
	rigidbody.velocity.x = glm::sign(rigidbody.velocity.x) * activeParams.velocity;
	rigidbody.velocity.z = glm::sign(rigidbody.velocity.z) * activeParams.velocity;
}