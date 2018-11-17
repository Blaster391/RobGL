#include "LightPool.h"


namespace rgl {

	LightPool::LightPool(const std::vector<Shader*>& shaders,  Camera* c, ScreenInformationUniform* screenInfoUnform, GLuint depthTex, GLuint normalsTex) :
		RenderPool(shaders, c), _depthTex(depthTex), _normalsTex(normalsTex)
	{
		addUniformData(screenInfoUnform);
	}


	LightPool::~LightPool()
	{
	}

	void LightPool::addLight(PointLight * light)
	{
		_renderObjects.push_back(light);
	}

	void LightPool::drawData(float delta)
	{

		glCullFace(GL_FRONT);
		glBlendFunc(GL_ONE, GL_ONE);
		
		glUniform1i(glGetUniformLocation(_program, "depthTex"), 3);
		glUniform1i(glGetUniformLocation(_program, "normalsTex"), 4);

		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, _depthTex);
		glActiveTexture(GL_TEXTURE4);
		glBindTexture(GL_TEXTURE_2D, _normalsTex);

		for (auto& l : _renderObjects) {
			l->draw(delta, _program);
		}


		glActiveTexture(GL_TEXTURE0);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glCullFace(GL_BACK);



	}

}
