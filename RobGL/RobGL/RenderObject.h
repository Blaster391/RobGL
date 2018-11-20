#pragma once
#include "Mesh.h"
#include "Texture.h"
#include <External/glm/mat4x4.hpp>
#include "BoundingSphere.h"

namespace rgl {

	class RenderObject
	{
	public:
		RenderObject();
		~RenderObject();

		inline glm::mat4 getModelMatrix() {
			return _modelMatrix;
		}

		inline void setModelMatrix(glm::mat4x4 m) {
			_modelMatrix = m;
		}

		inline void setMesh(Mesh* m) {
			_mesh = m;
		}

		inline void setTexture(Texture* t) {
			_texture = t;
		}

		virtual void draw(float delta, GLuint program);

		inline void setBounds(BoundingSphere* bounds) {
			_bounds = bounds;
		}

		inline BoundingSphere* getBounds() {
			return _bounds;
		}

		glm::vec3 getPosition();

	protected:
		glm::mat4x4 _modelMatrix = glm::mat4(1);

	private:
		Mesh* _mesh = nullptr;
		Texture* _texture = nullptr;



		BoundingSphere* _bounds = nullptr;
	};

}

