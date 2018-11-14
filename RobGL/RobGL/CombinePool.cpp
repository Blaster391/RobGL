#include "CombinePool.h"
#include "FixedScreenCamera.h"
#include "MeshHelpers.h"

namespace rgl {
	CombinePool::CombinePool(const std::vector<Shader*>& shaders, GLuint& bufferColourTex, GLuint emissiveTex, GLuint specularTex) : 
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

	void CombinePool::drawData(float delta)
	{

		glUniform1i(glGetUniformLocation(_program,"colourTex"), 2);
		glUniform1i(glGetUniformLocation(_program, "emissiveTex"), 3);
		glUniform1i(glGetUniformLocation(_program, "specularTex"), 4);
		
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, _bufferColourTex);

		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, _emissiveTex);

		glActiveTexture(GL_TEXTURE4);
		glBindTexture(GL_TEXTURE_2D, _specularTex);

		_quadObject->draw(delta,_program);

		glActiveTexture(GL_TEXTURE0);
	}

}