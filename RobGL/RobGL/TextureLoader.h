#pragma once
#include "Texture.h"
#include <string>
namespace rgl {
	class TextureLoader
	{
	public:
		static Texture* LoadFromPNG(std::string filename, bool generateMips);
	};
}
