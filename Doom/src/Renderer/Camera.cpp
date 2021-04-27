#include "pch.h"
#include "Camera.h"

Camera::Camera()
	: Camera(glm::vec3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f)
{
}

Camera::Camera(const glm::vec3& position, float rotationX, float rotationY)
	: position(position), rotationX(rotationX), rotationY(rotationY)
{
	UpdateLookAtPosition();
}

void Camera::MoveAlong(float value)
{
	position += value * RotatePosition(0.0f, rotationY);
	UpdateLookAtPosition();
}

void Camera::MoveHorizonally(float value)
{
	position += value * RotatePosition(0, rotationY + consts::PI / 2.0f);
	UpdateLookAtPosition();
}

void Camera::MoveVertically(float value)
{
	UpdateLookAtPosition();
}

void Camera::RotateX(float value)
{
	this->rotationX += value;
	UpdateLookAtPosition();
}

void Camera::RotateY(float value)
{
	this->rotationY += value;
	UpdateLookAtPosition();
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

void Camera::SetRotationY(float value)
{
	this->rotationY = value;
	UpdateLookAtPosition();
}

glm::vec3 Camera::RotatePosition(float angleX, float angleY) const
{
	glm::vec4 dir = glm::vec4(0.0f, 0.0f, 1.0f, 0.0f);
	glm::mat4 M(1.0f);
	M = glm::rotate(M, angleY, glm::vec3(0.0f, 1.0f, 0.0f));
	M = glm::rotate(M, angleX, glm::vec3(1.0f, 0.0f, 0.0f));
	dir = M * dir;
	return glm::vec3(dir);
}

void Camera::UpdateLookAtPosition()
{
	lookAtPosition = position + RotatePosition(rotationX, rotationY);
}
