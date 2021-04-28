#pragma once

class Camera
{
private:
	static Camera* instance;
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 rotation;
	glm::vec3 rotationStep;
	glm::vec3 movementStep;

public:
	static Camera* GetInstance(const glm::vec3& position = glm::vec3(0), const glm::vec3& rotation = glm::vec3(0));
	void Update(float deltaTime);
	static void Destroy();

	void SetPosition(const glm::vec3& position);
	void SetFront(const glm::vec3& front);

	inline const glm::vec3& GetPosition() const { return position; }
	inline const glm::vec3& GetFront() const { return front; }
	inline glm::vec3 GetLootAtPosition() const { return position + front; }

	void Move(glm::vec3 values) { MoveX(values.x); MoveY(values.y); MoveZ(values.z); }
	void MoveX(float value);
	void MoveY(float value);
	void MoveZ(float value);

	void Rotate(glm::vec3 angles) { this->rotation += angles; }
	void RotateX(float angle) { this->rotation.x += angle; }
	void RotateY(float angle) { this->rotation.y += angle; }
	void RotateZ(float angle) { this->rotation.z += angle; }

	void SetRotation(glm::vec3 rotation) { this->rotation = rotation; }
	void SetRotationX(float rotationX) { this->rotation.x = rotationX; }
	void SetRotationY(float rotationY) { this->rotation.y = rotationY; }
	void SetRotationZ(float rotationZ) { this->rotation.z = rotationZ; }

	inline glm::vec3 GetRotation() const { return rotation; }

	void SetRotationStep(glm::vec3 rotationStep) { this->rotationStep = rotationStep; }
	void SetRotationStepX(float rotationStepX) { this->rotationStep.x = rotationStepX; }
	void SetRotationStepY(float rotationStepY) { this->rotationStep.y = rotationStepY; }
	void SetRotationStepZ(float rotationStepZ) { this->rotationStep.z = rotationStepZ; }

	inline glm::vec3 GetRotationStep() const { return rotationStep; }

	void SetMovementStep(glm::vec3 movementStep) { this->movementStep = movementStep; }
	void SetMovementStepX(float movementStepX) { this->movementStep.x = movementStepX; }
	void SetMovementStepY(float movementStepY) { this->movementStep.y = movementStepY; }
	void SetMovementStepZ(float movementStepZ) { this->movementStep.z = movementStepZ; }

	inline glm::vec3 GetMovementStep() const { return movementStep; }

private:
	Camera(const glm::vec3& position, glm::vec3 rotation);

	glm::vec3 RotatePosition(glm::vec3 rotation) const;
};

