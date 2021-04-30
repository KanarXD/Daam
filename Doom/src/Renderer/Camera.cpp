#include "pch.h"
#include "Camera.h"

Camera* Camera::instance = nullptr;

Camera* Camera::GetInstance(const glm::vec3& position, const glm::vec3& rotation)
{
	if (instance == nullptr) instance = new Camera(position, rotation);
	return instance;
}

void Camera::Update(float deltaTime)
{
	// Rotate(rotationStep * deltaTime);
	rotation.y = atan2(front.x, front.z);
	Move(movementStep * deltaTime);
	// front = RotatePosition(rotation);
}

void Camera::Destroy() {
	delete instance;
}

Camera::Camera(const glm::vec3& position, glm::vec3 rotation)
	: position(position), rotation(rotation), rotationStep(glm::vec3(0)), movementStep(glm::vec3(0))
{
	front = RotatePosition(rotation);
}

void Camera::MoveX(float value)
{
	position += value * RotatePosition(glm::vec3(0, rotation.y + glm::pi<float>() / 2.0f, 0));
}

void Camera::MoveY(float value)
{
	this->rotationX += value;
	UpdateLookAtPosition();
}

void Camera::MoveZ(float value)
{
	position += value * RotatePosition(glm::vec3(0, rotation.y, 0));
}

void Camera::SetPosition(const glm::vec3& position)
{
	this->position = position;
	UpdateLookAtPosition();
}

void Camera::SetRotationX(float value)
{
	this->rotationX = value;
	UpdateLookAtPosition();
}

void Camera::SetFront(const glm::vec3& front) 
{
	this->front = front;
}

glm::vec3 Camera::RotatePosition(glm::vec3 rotation) const
{
	glm::vec4 dir = glm::vec4(0, 0, 1, 0);
	glm::mat4 M(1);
	M = glm::rotate(M, rotation.z, glm::vec3(0, 0, 1));
	M = glm::rotate(M, rotation.y, glm::vec3(0, 1, 0));
	M = glm::rotate(M, rotation.x, glm::vec3(1, 0, 0));
	dir = M * dir;
	return glm::vec3(dir);
}

void Camera::UpdateLookAtPosition()
{
	lookAtPosition = position + RotatePosition(rotationX, rotationY);
}
