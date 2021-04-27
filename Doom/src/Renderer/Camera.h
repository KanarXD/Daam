#pragma once

class Camera
{
private:
	glm::vec3 position;
	glm::vec3 lookAtPosition;
	float rotationX;
	float rotationY;
public:
	Camera();

	Camera(const glm::vec3& position, float rotationX, float rotationY);

	void SetPosition(const glm::vec3& position);

	void SetRotationX(float value);

	void SetRotationY(float value);

	void MoveAlong(float value);

	void MoveHorizonally(float value);

	void MoveVertically(float value);

	void RotateX(float value);

	void RotateY(float value);

	inline const glm::vec3& GetPosition() const { return position; }

	inline const glm::vec3& GetLootAtPosition() const { return lookAtPosition; }

	inline float GetRotationX() const { return rotationX; }

	inline float GetRotationY() const { return rotationY; }

private:
	glm::vec3 RotatePosition(float angleX, float angleY) const;

	void UpdateLookAtPosition();
};

