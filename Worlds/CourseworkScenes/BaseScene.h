#pragma once

#include <RobGL/Renderer.h>

class BaseScene
{
public:
	BaseScene(Window& window);
	~BaseScene();

	virtual void onResize(int width, int height);

	virtual void draw(float delta);

protected:
	rgl::Renderer _renderer;
};

