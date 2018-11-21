#pragma once
#include "BaseUniform.h"
#include "Cubemap.h"
namespace rgl {
	class WaterUniform :
		public BaseUniform
	{
	public:
		WaterUniform(Cubemap* reflection);
		~WaterUniform();

		void update(float delta);
		virtual void apply(GLuint program) override;
	private:
		float _time = 0;
		float _maxDisplacement = 0.5f;
		Cubemap* _reflection;
	};
}


