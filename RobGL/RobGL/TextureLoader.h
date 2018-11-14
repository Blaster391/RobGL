#pragma once
#include "Texture.h"
#include "Cubemap.h"
#include <string>
#include <vector>
namespace rgl {
	class TextureLoader
	{
	public:
		static Texture* LoadFromFile(std::string filename, bool hasAlpha, bool generateMips = true);
		static Cubemap* LoadCubemapFromFile(std::vector<std::string> faces, bool generateMips = true);
	};
}
