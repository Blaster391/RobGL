#pragma once
#include "RenderObject.h"
namespace rgl {
	class PointLight
		: public RenderObject
	{
	public:
		PointLight(glm::vec4 colour);
		~PointLight();
		virtual void draw(float delta, GLuint program) override;
		void setColour(glm::vec4 colour);
		glm::vec4 getColour();
	private:
		glm::vec4 _colour;
	};
}
