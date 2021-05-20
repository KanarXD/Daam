#include "pch.h"
#include "RigidBody.h"

RigidBody::RigidBody(glm::vec3 angularVelocity, glm::vec3 velocity)
	: angularVelocity(angularVelocity), velocity(velocity) {}
