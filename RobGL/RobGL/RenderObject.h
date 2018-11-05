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

		inline void setModelMatrix(glm::mat4x4 m) {
			_modelMatrix = m;
		}

		inline void setMesh(Mesh* m) {
			_mesh = m;
		}

		inline void setTexture(Texture* t) {
			_texture = t;
		}

		virtual void draw(GLuint program);

		inline void setBounds(BoundingSphere* bounds) {
			_bounds = bounds;
		}

		inline BoundingSphere* getBounds() {
			return _bounds;
		}

		glm::vec3 getPosition();

	private:
		Mesh* _mesh = nullptr;
		Texture* _texture = nullptr;
		glm::mat4x4 _modelMatrix;

		BoundingSphere* _bounds = nullptr;
	};

}

