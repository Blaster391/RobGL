#pragma once
#include "BaseUniform.h"
namespace rgl {
	class WaterUniform :
		public BaseUniform
	{
	public:
		WaterUniform();
		~WaterUniform();

		void update(float delta);
		virtual void apply(GLuint program) override;
	private:
		float _time;
		float _maxDisplacement = 3.0f;
	};
}


