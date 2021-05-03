#pragma once

struct RigidBody
{
	glm::vec3 angularVelocity;
	glm::vec3 velocity;

	RigidBody();
	RigidBody(glm::vec3 angularVelocity, glm::vec3 velocity);

};

