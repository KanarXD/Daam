#pragma once

struct RigidBody
{
	glm::vec3 angularVelocity;
	glm::vec3 velocity;

	RigidBody(glm::vec3 angularVelocity = glm::vec3(0), glm::vec3 velocity = glm::vec3(0));

};

