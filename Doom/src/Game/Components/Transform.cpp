#include "pch.h"
#include "Transform.h"

Transform::Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
	: position(position), rotation(rotation), scale(scale) {}

void Transform::Update(const RigidBody& rigidbody, float dt)
{
	rotation += rigidbody.angularVelocity * dt;
	position.y += rigidbody.velocity.y * dt;
	position += rigidbody.velocity.x * RotatePosition(glm::vec3(0, rotation.y + glm::half_pi<float>(), 0)) * dt;
	position += rigidbody.velocity.z * RotatePosition(glm::vec3(0, rotation.y, 0)) * dt;
	
}

glm::vec3 Transform::RotatePosition(glm::vec3 rotation) const
{
	glm::vec4 dir = glm::vec4(0, 0, 1, 0);
	glm::mat4 M(1);
	M = glm::rotate(M, rotation.z, glm::vec3(0, 0, 1));
	M = glm::rotate(M, rotation.y, glm::vec3(0, 1, 0));
	M = glm::rotate(M, rotation.x, glm::vec3(1, 0, 0));
	dir = M * dir;
	return glm::vec3(dir);
}

std::ostream& operator<<(std::ostream& os, const Transform& transform)
{
	os << " -----\n" <<
		"Position: (" << transform.position.x << ", " << transform.position.y << ", " << transform.position.z << ")\n" <<
		"Rotation: (" << transform.rotation.x << ", " << transform.rotation.y << ", " << transform.rotation.z << ")\n" <<
		"Scale:    (" << transform.scale.x    << ", " << transform.scale.y    << ", " << transform.scale.z    << ")\n";
	return os;
}
