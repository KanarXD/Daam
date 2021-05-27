#include "pch.h"
#include "Enemy.h"
#include "Game/Player.h"
#include "Game/GameObjectManager.h"
#include "Renderer/Renderer.h"

Enemy::Specs Enemy::defualtSpecs{ Combat(), 120, 100, 10 };

Enemy::Specs::Specs(const Combat& combat, float fov, float viewDist, float speed)
	: combat(combat), fov(fov), viewDist(viewDist), speed(speed) {}


Enemy::Enemy(const Transform& transform, const std::string& type)
	: GameObject(transform, type),  rigidbody(), activeSpecs(Enemy::defualtSpecs) 
{
	healthbar.offsetY = transform.scale.y * hitbox.scaleModifier.y + 1;
}

void Enemy::Update(float dt)
{
	GameObject::Update(dt);
	glm::vec3 playerPos = Player::GetInstance()->GetTransform().position;
	float inRange = glm::distance(transform.position, playerPos) < activeSpecs.viewDist;
	float angToPlayer = atan2(playerPos.x - transform.position.x, playerPos.z - transform.position.z);
	if (inRange)
	{
		healthbar.draw = true;
		healthbar.rotY = angToPlayer;
		if (PlayerInBound(playerPos, angToPlayer))
		{
			transform.rotation.y = angToPlayer;
			if (glm::distance(transform.position, playerPos) <= 10)
			{
				switch (attackingStage)
				{
				case -1:
					rigidbody.velocity.z = -50;
					break;
				case 0:
					if (timer - activeSpecs.combat.lastAttackTime > activeSpecs.combat.timeBetweenAttack)
					{
						activeSpecs.combat.lastAttackTime = timer;
						attackingStage = 1;
					}
					rigidbody.velocity.z = 0;
					break;
				case 1:
					rigidbody.velocity.z = 50;
					break;
				}
			}
			else
			{
				if (!attackingStage)
					rigidbody.velocity.z = activeSpecs.speed;
				else
					attackingStage = 0;
			}
		}
		else
			transform.rotation.y += (rand() % 20 - 10) / 200.0f;
	}
	else
	{
		transform.rotation.y += (rand() % 20 - 10) / 200.0f;
		rigidbody.velocity.z = activeSpecs.speed;
		healthbar.draw = false;
	}
	transform.Update(rigidbody, dt);
	healthbar.scaleX = activeSpecs.combat.health / activeSpecs.combat.maxHealth;
	transform.position.y += sin(timer * 2) / 100;
}

void Enemy::Draw()
{
	GameObject::Draw();
	if (healthbar.draw)
	{
		std::optional<const Model*> model = ModelsLibrary::GetInstance()->Get(Healthbar::modelPath);
		if (!model.has_value())
		{
			LOGERROR("Enemy - ModelsLibrary::Get(...) - ", Healthbar::modelPath);
			return;
		}

		Renderer::DrawModel(*model.value(),
			glm::scale(glm::rotate(glm::translate(glm::mat4(1.0f), transform.position + glm::vec3(0, healthbar.offsetY, 0)),
				healthbar.rotY, glm::vec3(0, 1, 0)), glm::vec3(healthbar.scaleX, 1, 1)));
	}
}

void Enemy::Collision(const GameObject& collidedObject)
{
	if (collidedObject.GetType() == "bullet")
	{
		activeSpecs.combat.health -= Player::GetInstance()->GetCombat().DealDamage();
	}
	else if (collidedObject.GetType() == "player")
	{
		attackingStage = -1;
	}
	else if (collidedObject.GetType() == "box")
	{
		glm::vec3 boxPos = collidedObject.GetTransformC().position + collidedObject.GetHitboxC().offset;
		glm::vec3 boxSize = collidedObject.GetTransformC().scale * collidedObject.GetHitboxC().scaleModifier;
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
}

bool Enemy::PlayerInBound(const glm::vec3& playerPos, float angToPlayer) const
{
	float angDiff = fabs(glm::degrees(angToPlayer - transform.rotation.y));
	if (angDiff > 180) angDiff -= 360;
	if (fabs(angDiff) > activeSpecs.fov / 2.0f) return false;

	return !GameObjectManager::GetInstance()->Raycast(transform.position, playerPos, "box");
	
	return true;
}
