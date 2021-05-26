#include "pch.h"
#include "Camera.h"

Camera::Camera(Transform transform, float fov)
	: transform(transform), fov(fov) {}

void Camera::SetTransform(const Transform& newTransform, float height)
{
	transform = newTransform; transform.position += height * glm::vec3(0, 1, 0);
}

glm::vec3 Camera::GetLootAtPosition() const
{
	return transform.position + front; //transform.RotatePosition(transform.rotation);
}
