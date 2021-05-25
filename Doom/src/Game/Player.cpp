#include "pch.h"
#include "Player.h"
#include "GameObjectManager.h"
#include "Renderer/Renderer.h"
#include "Renderer/Library/ModelsLibrary.h"
#include "Arsenal/Bullet.h"

Player* Player::instance = nullptr;

const Player::StateParams Player::walkParams{ 2.0f, 30.0f, 3.0f };
const Player::StateParams Player::sprintParams{ 2.0f, 50.0f, 3.0f };
const Player::StateParams Player::crouchParams{ 2.0f, 15.0f, 2.0f };

Player::StateParams Player::activeParams = Player::walkParams;

Combat Player::combat{ 1000, 30, 0.1f };
Hitbox Player::hitbox = GOModels.at("player").hitbox;
Transform Player::transform{};
RigidBody Player::rigidbody{};

Player::State Player::state = Player::State::Walk;

Camera Player::camera = Camera(Transform(), 50.0f);

float Player::timer{};
float Player::lastShootTime{};

void Player::Init(Transform startingTransform)
{
	if (instance == nullptr) instance = new Player(startingTransform);
}

void Player::Update(float dt)
{
	timer += dt;
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

void Player::Shoot()
{
	if (timer - lastShootTime > combat.attackTime)
	{
		lastShootTime = timer;
		GameObjectManager::GetInstance()->Add<Bullet>(
			Transform(transform.position + glm::vec3(0, activeParams.height - 0.5f, 0), transform.rotation, glm::vec3(5)));
	}
}

void Player::LookAt(glm::vec3 front)
{
	transform.rotation.y = atan2(front.x, front.z);
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