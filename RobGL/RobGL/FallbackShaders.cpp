#include "FallbackShaders.h"
#include "Shader.h"
namespace rgl {

	Shader* FallbackShaders::_vertex = nullptr;
	Shader* FallbackShaders::_fragment = nullptr;

	Shader* FallbackShaders::VertexShader()
	{
		if (_vertex == nullptr) {
			//TODO load fallback
		}

		return nullptr;
	}
	Shader* FallbackShaders::FragmentShader()
	{
		return nullptr;
	}

}