#include "CombinePool.h"
#include "FixedScreenCamera.h"
#include "MeshHelpers.h"

namespace rgl {
	CombinePool::CombinePool(const std::vector<Shader*>& shaders, GLuint bufferColourTex, GLuint emissiveTex, GLuint specularTex) : 
		RenderPool(shaders, new FixedScreenCamera), _bufferColourTex(bufferColourTex), _emissiveTex(emissiveTex), _specularTex(specularTex)
	{
		_camera->setProjectionOrthographic();
		_quadMesh = MeshHelpers::GenerateQuad();
		_quadObject = new RenderObject();
		_quadObject->setMesh(_quadMesh);
		_quadObject->setTexture(_quadTexture);
		_renderObjects.push_back(_quadObject);
	}
	CombinePool::~CombinePool()
	{
		delete _camera;
	}

	void CombinePool::draw(float delta)
	{
		beginDraw();

		glUniform1i(glGetUniformLocation(_program,"tex"), 2);
		glUniform1i(glGetUniformLocation(_program, "specularTex"), 4);
		
		glActiveTexture(GL_TEXTURE2);
		glActiveTexture(GL_TEXTURE3);

		glActiveTexture(GL_TEXTURE4);

		_quadMesh->draw(delta,_program);

		glActiveTexture(GL_TEXTURE0);

		endDraw();
	}

}