#pragma once
#include "Vec3/Vec3.h"
#include "mat4/mat4.h"

class Transfrom
{
public:
	void SetPosition(const lm::vec3& pos);
	void SetScale(const lm::vec3& scl);
	void SetRotation(const lm::vec3& rot);

	lm::vec3 GetPosition();
	lm::vec3 GetScale();
	lm::vec3 GetRotation();

	void Translate(const lm::vec3& trans);
	void AddScale(const lm::vec3& scl);
	void AddRotation(const lm::vec3& rot);
	void AddPosition(lm::vec3& pos);

	lm::mat4 calcMatrix() const;
	lm::mat4 Matrix;
private:

	lm::vec3 scale = lm::vec3(1);
	lm::vec3 position;
	lm::vec3 rotation;
};