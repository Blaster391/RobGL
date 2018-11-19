#pragma once
#include "RenderObject.h"
#include "AnimatedMesh.h"
namespace rgl {
	class AnimatedRenderObject
		: public RenderObject
	{
	public:
		AnimatedRenderObject();
		~AnimatedRenderObject();

		inline void setMesh(AnimatedMesh* m) {
			_mesh = m;
			RenderObject::setMesh(m);
		}

		virtual void draw(float delta, GLuint program) override;

		void setAnimation(int anim);
	protected:
		AnimatedMesh* _mesh;

	};

}

