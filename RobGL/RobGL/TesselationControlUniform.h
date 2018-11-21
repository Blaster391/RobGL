#pragma once
#include "BaseUniform.h"
namespace rgl {
	class TesselationControlUniform :
		public BaseUniform
	{
	public:
		TesselationControlUniform(const int outer[3], int inner);
		~TesselationControlUniform();

		void setTesselation(const int outer[3], int inner){
			_outer[0] = outer[0];
			_outer[1] = outer[1];
			_outer[2] = outer[2];

			_inner = inner;
		}

		virtual void apply(GLuint program) override;
	private:
		int _inner;
		int _outer[3];
	};
}
