#pragma once
#include "pch.h"
#include "RigidBody.h"

struct Transform
{
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	Transform(glm::vec3 position = glm::vec3(0), glm::vec3 rotation = glm::vec3(0), glm::vec3 scale = glm::vec3(1));

	void Update(const RigidBody& rigidbody, float dt);

	glm::vec3 RotatePosition(glm::vec3 rotation) const;

	friend std::ostream& operator<<(std::ostream& os, const Transform& transform);
};