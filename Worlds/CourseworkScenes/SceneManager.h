#pragma once
#include "BaseScene.h"
#include <Input/Input.h>

#include <vector>

class SceneManager
{
public:
	SceneManager(Input* input);
	~SceneManager();
	void addScene(BaseScene* scene);

	void onResize(int width, int height);

	bool update(float delta);

private:
	int _activeScene = 0;
	std::vector<BaseScene*> _scenes;
	Input* _input;
};

