#pragma once
#include "Texture.h"
#include <string>
namespace rgl {
	class TextureLoader
	{
	public:
		static Texture* LoadFromFile(std::string filename, bool hasAlpha, bool generateMips = true);
	};
}
