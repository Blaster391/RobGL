#include "SceneNode.h"

namespace rgl {
	namespace scenes {

		SceneNode::SceneNode()
		{
		}


		SceneNode::~SceneNode()
		{
		}

		glm::mat4 SceneNode::getWorldTransform()
		{
			return _worldTransform;
		}

		glm::mat4 SceneNode::updateWorldTransform()
		{
			glm::mat4 t;

			if (_parent != nullptr) {
				t = _parent->getWorldTransform();
			}


			 glm::mat4 localTransform = glm::translate(glm::rotate(glm::scale()));
			 t = t * localTransform;

			if (_renderObject != nullptr) {
				_renderObject->setModelMatrix(t);
			}

			if (_worldTransform != t) {
				_worldTransform = t;
				for (auto& c : _children) {
					c->updateWorldTransform();
				}
			}

			return t;
		}

		void SceneNode::addChild(SceneNode * sn)
		{
			_children.push_back(sn);
		}
		void SceneNode::attachRenderObject(RenderObject * ro)
		{
			_renderObject = ro;
		}
		SceneNode * SceneNode::getParent()
		{
			return _parent;
		}
		void SceneNode::setParent(SceneNode* p)
		{
			_parent = p;
		}
		void SceneNode::setPosition(glm::vec3 p)
		{
			_position = p;
			updateWorldTransform();

		}
		void SceneNode::setRotation(glm::vec4 r)
		{
			_rotation = r;
			updateWorldTransform();
		}
		void SceneNode::setScale(glm::vec3 s)
		{
			_scale = s;
			updateWorldTransform();
		}
	}
}