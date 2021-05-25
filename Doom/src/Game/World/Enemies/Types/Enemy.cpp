#include "pch.h"
#include "Enemy.h"
#include "Game/Player.h"
#include "Game/GameObjectManager.h"
#include "Renderer/Renderer.h"

Enemy::Specs Enemy::defualtSpecs{ Combat(), 120, 100, 35 };

Enemy::Specs::Specs(const Combat& combat, float fov, float viewDist, float speed)
	: combat(combat), fov(fov), viewDist(viewDist), speed(speed) {}


Enemy::Enemy(const Transform& transform, const std::string& type)
	: GameObject(transform, type),  rigidbody(), activeSpecs(Enemy::defualtSpecs) 
{
	// this->transform.rotation.y = float(rand() % 100) / 24;
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
	}

	if (inRange && PlayerInBound(playerPos, angToPlayer))
	{
		transform.rotation.y = angToPlayer;
		// rigidbody.velocity.z = activeSpecs.speed;
	}
	else
	{
		rigidbody.velocity.z = 0;
		healthbar.draw = false;
	}
	activeSpecs.combat.health -= 5;
	transform.Update(rigidbody, dt);
	healthbar.scaleX = activeSpecs.combat.health / activeSpecs.combat.maxHealth;
	transform.position.y += sin(timer * 2) / 50;
}

void Enemy::Draw()
{
	GameObject::Draw();
	if (healthbar.draw)
	{
		std::optional<const Model*> model = ModelsLibrary::GetInstance()->Get(Healthbar::modelPath);
		if (!model.has_value())
		{
			LOGERROR("Enemy - ModelsLibrary::Get(...) - ", modelPath);
			return;
		}

		Renderer::DrawModel(*model.value(),
			glm::scale(glm::rotate(glm::translate(glm::mat4(1.0f), transform.position + glm::vec3(0, healthbar.offsetY, 0)),
				healthbar.rotY, glm::vec3(0, 1, 0)), glm::vec3(healthbar.scaleX, 1, 1)));
	}
}

void Enemy::Collision(const GameObject& collidedObject)
{
}

bool Enemy::PlayerInBound(const glm::vec3& playerPos, float angToPlayer) const
{
	float angDiff = fabs(glm::degrees(angToPlayer - transform.rotation.y));
	if (angDiff > 180) angDiff -= 360;
	if (fabs(angDiff) > activeSpecs.fov / 2.0f) return false;

	return !GameObjectManager::GetInstance()->Raycast(transform.position, playerPos, "box");
	
	return true;
}
