#pragma once
#include "GameObjectsModels.h"
#include "Components/Hitbox.h"
#include "Components/Transform.h"

class GameObject
{
protected:
	Hitbox hitbox;
	Transform transform;
	std::string modelPath;
	std::string type;
	double timer;

public:
	GameObject(const Transform& transform, const std::string& type);
	virtual void Update(float dt);
	virtual void Draw();

	virtual void Collision(const GameObject& collidedObject) {};

	Hitbox& GetHitbox() { return hitbox; }
	Transform& GetTransform() { return transform; }
	const std::string& GetType() { return type; }
};

