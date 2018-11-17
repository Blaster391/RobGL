#pragma once
#include "BaseUniform.h"
namespace rgl {
	class ScreenInformationUniform : public BaseUniform
	{
	public:
		ScreenInformationUniform(int width, int height);
		~ScreenInformationUniform();

		virtual void apply(GLuint program) override;

		void updateScreenSize(int width, int height);
	private:
		int _width;
		int _height;
	};
}

