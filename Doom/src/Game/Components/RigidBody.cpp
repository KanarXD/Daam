#include "pch.h"
#include "RigidBody.h"

RigidBody::RigidBody()
	: angularVelocity(glm::vec3(0)), velocity(glm::vec3(0)) {}

RigidBody::RigidBody(glm::vec3 angularVelocity, glm::vec3 velocity)
	: angularVelocity(angularVelocity), velocity(velocity) {}
