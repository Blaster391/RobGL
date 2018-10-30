#pragma once
#include <string>
#include "glad/glad.h"
namespace rgl {
	class Shader
	{
	public:
		Shader(std::string filepath, GLenum type);
		~Shader();

		inline GLuint pointer() {
			return _pointer;
		}

		inline bool loaded() {
			return _loaded;
		}

	private:
		bool _loaded = false;
		bool _failed = false;

		GLenum _shaderType;

		std::string loadShaderFile();

		GLuint _pointer;

		std::string _filepath;
	};

}

