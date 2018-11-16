#include "LightPool.h"


namespace rgl {

	LightPool::LightPool(const std::vector<Shader*>& shaders, Camera* c, GLuint depthTex, GLuint normalsTex) : 
		RenderPool(shaders, c), _depthTex(depthTex), _normalsTex(normalsTex)
	{
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
		//glClearColor(0, 0, 0, 1);
		//glClear(GL_COLOR_BUFFER_BIT);

		glCullFace(GL_FRONT);
		glBlendFunc(GL_ONE, GL_ONE);
		
		glUniform1i(glGetUniformLocation(_program, "depthTex"), 3);
		glUniform1i(glGetUniformLocation(_program, "normalsTex"), 4);

		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, _depthTex);
		glActiveTexture(GL_TEXTURE4);
		glBindTexture(GL_TEXTURE_2D, _normalsTex);


		//TODO !!!
		glUniform2f(glGetUniformLocation(_program, "pixelSize"), 1.0f / 800, 1.0f / 600);

		for (auto& l : _renderObjects) {
			l->draw(delta, _program);
		}


		glActiveTexture(GL_TEXTURE0);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glCullFace(GL_BACK);



	}

}
