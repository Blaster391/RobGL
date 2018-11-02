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

		glUseProgram(_program);
		_viewMatrixPosition = glGetUniformLocation(_program, "viewMatrix");
		_projectionMatrixPosition = glGetUniformLocation(_program, "projMatrix");
		glUseProgram(0);
	}

	RenderPool::~RenderPool()
	{
	}

	void RenderPool::addRenderObject(RenderObject* r) {
		_renderObjects.push_back(r);
	}

	void rgl::RenderPool::draw()
	{
		if (!_enabled) {
			return;
		}

		glUseProgram(_program);

		setUniforms();



		if (_scissor) {
			glEnable(GL_SCISSOR_TEST);
			glScissor(_scissorBounds.x, _scissorBounds.y, _scissorBounds.Width, _scissorBounds.Height);
		}
		else {
			glDisable(GL_SCISSOR_TEST);
		}

		for (auto& r : _renderObjects) {
			r->draw(_program);
		}

		glUseProgram(0);
	}

	void RenderPool::setScissor(bool active)
	{
		_scissor = active;
	}

	void RenderPool::setScissorBounds(Box b)
	{
		_scissorBounds = b;
	}

	void RenderPool::setEnabled(bool active)
	{
		_enabled = active;
	}


	void RenderPool::setUniforms()
	{
		//TODO these are using gets and that's bad
		glUniformMatrix4fv(_viewMatrixPosition, 1, false, (float*)&_camera->getViewMatrix());
		glUniformMatrix4fv(_projectionMatrixPosition, 1, false, (float*)&_camera->getProjectionMatrix());
	}
}



