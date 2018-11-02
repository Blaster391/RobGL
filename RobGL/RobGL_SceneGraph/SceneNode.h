#pragma once
#include <RobGL/RenderObject.h>
#include <vector>
#include <External/glm/common.hpp>
namespace rgl {
	namespace scenes {
		class SceneNode
		{
		public:
			SceneNode();
			~SceneNode();

			glm::mat4 getWorldTransform();
			glm::mat4 updateWorldTransform();

			void addChild(SceneNode* sn);
			void attachRenderObject(RenderObject* ro);

			SceneNode* getParent();
			void setParent(SceneNode* p);

			void setPosition(glm::vec3 p);
			void setRotation(glm::vec4  r);
			void setScale(glm::vec3 s);

		private:
			SceneNode* _parent = nullptr;

			RenderObject* _renderObject = nullptr;
			std::vector<SceneNode*> _children;

			glm::mat4 _worldTransform;

			glm::vec3 _position;
			glm::vec4 _rotation;
			glm::vec3 _scale;
		};
	}
}


