#include "Shader.h"
#include <iostream>
#include <fstream>

namespace rgl {
	Shader::Shader(std::string filepath, GLenum type) : _filepath(filepath), _shaderType(type)
	{
		std::string input = loadShaderFile();

		_pointer = glCreateShader(_shaderType);

		const char* chars = input.c_str();
		glShaderSource(_pointer, 1, &chars, NULL);
		glCompileShader(_pointer);

		GLint status;
		glGetShaderiv(_pointer, GL_COMPILE_STATUS, &status);

		if (status == GL_FALSE) {
			std::cout << "Compiling failed! Error log as follows:" << std::endl;
			char error[2048];
			glGetShaderInfoLog(_pointer, sizeof(error), nullptr, error);
			std::cout << error << std::endl;
			_failed = false;
			return;
		}
		std::cout << "Compiling success!" << std::endl << std::endl;

		_loaded = true;
	}

	Shader::~Shader()
	{
	}



	std::string Shader::loadShaderFile()
	{
		std::ifstream file;
		std::string input;

		file.open(_filepath);
		if (!file) {
			std::cout << "File does not exist!" << std::endl;
			_failed = true;
			return "";
		}

		file.seekg(0, std::ios::end);
		input.resize(1 + (unsigned int)file.tellg());
		file.seekg(0, std::ios::beg);
		file.read(&input[0], input.size());

		input[input.size() - 1] = '\n';

		std::cout << input << std::endl << std::endl;

		file.close();

		return input;
	}
}
