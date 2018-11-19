#pragma once
#include "BaseUniform.h"
#include "Texture.h"
#include <string>
namespace rgl {
	class AdditionalTextureUniform : public BaseUniform
	{
	public:
		AdditionalTextureUniform(Texture* texture, std::string textureName);
		~AdditionalTextureUniform();

		virtual void apply(GLuint program) override;
	private:
		std::string _textureName;
		Texture* _texture;
	};

}

