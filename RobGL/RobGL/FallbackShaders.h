#pragma once
namespace rgl {
	class Shader;

	class FallbackShaders
	{
	public:
		static Shader* VertexShader();
		static Shader* FragmentShader();

	private:
		static Shader* _vertex;
		static Shader* _fragment;
	};
}

