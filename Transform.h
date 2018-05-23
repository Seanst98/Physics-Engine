/*#pragma once
#include <glm.hpp>
#include "gtc\type_ptr.hpp"
#include "gtc\matrix_transform.hpp"
#include "gtx\matrix_transform_2d.hpp"

class Transform
{
public:
	Transform();
	~Transform();

	glm::mat3 getTransform()
	{
		if (needUpdate)
		{
			updateMatrix();
		}

		return transform;
	}

	glm::fmat3 getInverseTransform()
	{
		if (needUpdate)
		{
			updateMatrix();
		}

		return glm::inverse(transform);
	}

	inline Transform& setTranslation(vec2f p) { translation = p; needUpdate = true; return *this; }
	inline Transform& translate(vec2f p) { translation += p; needUpdate = true; return *this; }
	inline vec2f getTranslation() { return translation; }

	inline Transform& setRotation(float p) { rotation = p; needUpdate = true; return *this; }
	inline Transform& rotate(float p) { rotation += p; needUpdate = true; return *this; }
	inline float getRotation() { return rotation; }

	inline Transform& setScale(vec2f p) { scalem = p; needUpdate = true; return *this; }
	inline Transform& scale(vec2f p) { scalem *= p; needUpdate = true; return *this; }
	inline Transform& scale(float p) { scalem = scalem * p; needUpdate = true; return *this; }
	inline vec2f getScale() { return scalem; }

	inline Transform& setOrigin(vec2f p) { origin = p; return *this; }
	inline vec2f getOrigin() { return origin; }

	inline void saveToStream(std::ofstream& ofs)
	{
		ofs.write((char*)&translation, sizeof(translation));
		ofs.write((char*)&origin, sizeof(origin));
		ofs.write((char*)&rotation, sizeof(rotation));
		ofs.write((char*)&scalem, sizeof(scalem));
	}

	inline void loadFromStream(std::ifstream& ifs)
	{
		needUpdate = true;

		ifs.read((char*)&translation, sizeof(translation));
		ifs.read((char*)&origin, sizeof(origin));
		ifs.read((char*)&rotation, sizeof(rotation));
		ifs.read((char*)&scalem, sizeof(scalem));
	}

private:

	inline void updateMatrix()
	{
		needUpdate = false;

		glm::fmat3 ttranslate = glm::translate(glm::fmat3(), glm::fvec2(translation.x - origin.x, translation.y - origin.y));
		glm::fmat3 sscale = glm::scale(glm::fmat3(), glm::fvec2(scalem.x, scalem.y));
		glm::fmat3 rrotate = glm::rotate(glm::fmat3(), rotation);
		glm::fmat3 tttranslate = glm::translate(glm::fmat3(), glm::fvec2(origin.x, origin.y));

		transform = ttranslate * rrotate * sscale * tttranslate;

		glTransform[0].x = transform[0].x;
		glTransform[0].y = transform[0].y;
		glTransform[1].x = transform[1].x;
		glTransform[1].y = transform[1].y;

		glTransform[3].x = transform[2].x;
		glTransform[3].y = transform[2].y;
	}

	vec2f translation;
	vec2f origin;
	float rotation;
	vec2f scalem;

	bool needUpdate;
	glm::fmat3 transform;
	glm::fmat4 glTransform;
};*/