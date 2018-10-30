#include "RenderPool.h"
#include <iostream>
namespace rgl {

	RenderPool::RenderPool(const std::vector<Shader*>& shaders, Camera* c) : _camera(c)
	{
		_program = glCreateProgram();
		for (auto& s : shaders) {
			glAttachShader(_program, s->pointer());
		}
		glLinkProgram(_program);

		GLint status;
		glGetProgramiv(_program, GL_LINK_STATUS, &status);

		if (status == GL_FALSE) {
			std::cout << "Linking failed! Error log as follows:" << std::endl;
			char error[2048];
			glGetProgramInfoLog(_program, sizeof(error), NULL, error);
			std::cout << error << std::endl;
		}

	}

	RenderPool::~RenderPool()
	{
	}

	void RenderPool::addRenderObject(RenderObject* r) {
		_renderObjects.push_back(r);
	}

	void rgl::RenderPool::draw()
	{
		glUseProgram(_program);

		setUniforms();

		for (auto& r : _renderObjects) {
			r->draw(_program);
		}

		glUseProgram(0);
	}

	void RenderPool::setUniforms()
	{
		//TODO these are using gets and that's bad
		glUniformMatrix4fv(glGetUniformLocation(_program, "viewMatrix"), 1, false, (float*)&_camera->getViewMatrix());
		glUniformMatrix4fv(glGetUniformLocation(_program, "projMatrix"), 1, false, (float*)&_camera->getProjectionMatrix());
	}
}



