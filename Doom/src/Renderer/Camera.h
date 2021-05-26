#pragma once
#include "../Game/Components/Transform.h"

class Camera
{
private:
	Transform transform;
	glm::vec3 front{};

	float fov{ 50.0f };
	float nearClip{ 0.01f };
	float farClip{ 300.0f };

public:
	Camera(Transform transform, float fov);
	
	void SetTransform(const Transform& newTransform, float height);
	const Transform& GetTransform() const { return transform; }
	
	void SetFront(const glm::vec3& newFront) { front = newFront; }

	void SetFov(float newFov) { fov = newFov; }
	float GetFov() const { return fov * Consts::PI / 180.0f; }

	void SetNearClip(float newNearClip) { nearClip = newNearClip; }
	float GetNearClip() const { return nearClip; }

	void SetFarClip(float newFarClip) { farClip = newFarClip; }
	float GetFarClip() const { return farClip; }

	glm::vec3 GetLootAtPosition() const;
};

