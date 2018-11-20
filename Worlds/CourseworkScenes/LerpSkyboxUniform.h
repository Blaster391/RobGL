#pragma once
#include <RobGL/BaseUniform.h>
#include <RobGL/Cubemap.h>

class LerpSkyboxUniform : public rgl::BaseUniform
{
public:
	LerpSkyboxUniform(rgl::Cubemap* secondSkybox, rgl::Cubemap* thirdSkybox, float tweenTime);
	~LerpSkyboxUniform();

	void update(float delta);

	virtual void apply(GLuint program) override;
private:
	rgl::Cubemap* _secondSkybox;
	rgl::Cubemap* _thirdSkybox; 
	float _tweenTime;
	float _currentTime = 0.0f;
};

