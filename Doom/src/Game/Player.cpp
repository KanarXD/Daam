#include "pch.h"
#include "Player.h"
#include "GameObjectManager.h"
#include "Renderer/Renderer.h"
#include "Renderer/Library/ModelsLibrary.h"
#include "Arsenal/Bullet.h"
#include "Window/Window.h"


std::shared_ptr<Player> Player::GetInstance()
{
	static std::shared_ptr<Player> playerInstance(new Player());
	return playerInstance;
}

void Player::SetTransform(Transform startingTransform)
{
	this->transform = startingTransform;
}

void Player::Update(float dt)
{
	timer += dt;

	if (combat.IsDead())
	{
		gameState = GameState::GameOver;
		Window::GetInstance()->SetWindowShouldClose();
	}
	if (transform.position.y > 0)
		rigidbody.velocity.y -= 2 * Consts::G * dt;
	else if (transform.position.y < 0)
	{
		transform.position.y = 0.0f;
		rigidbody.velocity.y = 0.0f;
	}

	transform.Update(rigidbody, dt);
	camera.SetTransform(transform, activeParams.height);
	if (isShoot) Shoot();
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
	else
	{
		combat.health -= dynamic_cast<Enemy*>(&collidedObject)->GetSpecs().combat.DealDamage();
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

void Player::Shoot()
{
	if (timer - combat.lastAttackTime > combat.timeBetweenAttack)
	{
		combat.lastAttackTime = timer;
		GameObjectManager::GetInstance()->Add<Bullet>(
			Transform(transform.position + glm::vec3(0, activeParams.height - 0.5f, 0), transform.rotation, glm::vec3(5)));
	}
}

void Player::LookAt(glm::vec3 front)
{
	camera.SetFront(front);
	transform.rotation.y = atan2(front.x, front.z);
}

void Player::UpdateVelocity()
{
	rigidbody.velocity.x = glm::sign(rigidbody.velocity.x) * activeParams.velocity;
	rigidbody.velocity.z = glm::sign(rigidbody.velocity.z) * activeParams.velocity;
}