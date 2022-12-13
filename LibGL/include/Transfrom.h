#pragma once
#include "Vec3/Vec3.h"
#include "mat4/mat4.h"

class Transfrom
{
public:
	void setPosition(lm::vec3 pos);
	void setScale(lm::vec3 scl);
	void setRotation(lm::vec3 rot);

	lm::vec3 getPosition();
	lm::vec3 getScale();
	lm::vec3 getRotation();

	void translate(lm::vec3 trans);
	void addScale(lm::vec3 scl);
	void addRotation(lm::vec3 rot);
	void addPosition(lm::vec3 pos);

	lm::mat4 calcMatrix();
	lm::mat4 Matrix;
private:

	lm::vec3 scale = lm::vec3(1);
	lm::vec3 position;
	lm::vec3 rotation;
};