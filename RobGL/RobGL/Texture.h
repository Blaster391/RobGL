#pragma once
#include "glad/glad.h"
namespace rgl {
	class Texture
	{
	public:
		Texture(GLuint texture, bool mipmapped);
		~Texture();

		inline GLuint pointer() {
			return _pointer;
		}

		inline void bind() {
			glBindTexture(GL_TEXTURE_2D, _pointer);
		}

		inline void unbind() {
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		void setFiltering(bool enable);
	private:
		GLuint _pointer;

		bool _mipmapped;
	};
}
