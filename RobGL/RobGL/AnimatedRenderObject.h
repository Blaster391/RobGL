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
			if (_skeleton != nullptr) {
				delete _skeleton;
			}
			_skeleton = m->generateSkeleton();
			setActiveAnimation(0);
			RenderObject::setMesh(m);
		}

		virtual void draw(float delta, GLuint program) override;

		void setGlobalTransform(glm::mat4 transform);
		void setActiveAnimation(int anim, float offset = 0.0f);

	protected:
		AnimatedMesh* _mesh;
		Animation _activeAnimation;


		Skeleton* _skeleton = nullptr;

	};

}

