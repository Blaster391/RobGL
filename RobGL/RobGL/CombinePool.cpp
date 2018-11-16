#include "CombinePool.h"
#include "FixedScreenCamera.h"
#include "MeshHelpers.h"

namespace rgl {
	CombinePool::CombinePool(const std::vector<Shader*>& shaders, GLuint& bufferColourTex, GLuint emissiveTex, GLuint specularTex, bool useShadows, GLuint shadowTex) :
		RenderPool(shaders, new FixedScreenCamera), _bufferColourTex(bufferColourTex), _emissiveTex(emissiveTex), _specularTex(specularTex), _shadowTex(shadowTex), _useShadows(useShadows)
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

		glUniform1i(glGetUniformLocation(_program, "useShadows"), _useShadows);

		glUniform1i(glGetUniformLocation(_program,"colourTex"), 2);
		glUniform1i(glGetUniformLocation(_program, "emissiveTex"), 3);
		glUniform1i(glGetUniformLocation(_program, "specularTex"), 4);
		glUniform1i(glGetUniformLocation(_program, "shadowTex"), 5);

		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, _bufferColourTex);

		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, _emissiveTex);

		glActiveTexture(GL_TEXTURE4);
		glBindTexture(GL_TEXTURE_2D, _specularTex);

		glActiveTexture(GL_TEXTURE5);
		glBindTexture(GL_TEXTURE_2D, _shadowTex);

		glActiveTexture(GL_TEXTURE0);

		_quadObject->draw(delta,_program);

	}

}