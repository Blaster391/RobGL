#include "SceneManager.h"

SceneManager::SceneManager(Input * input) : _input(input)
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::addScene(BaseScene * scene)
{
	_scenes.push_back(scene);
}

void SceneManager::onResize(int width, int height)
{
	for (auto& scene : _scenes) {
		scene->onResize(width, height);
	}
}

bool SceneManager::update(float delta)
{
	if (_scenes.size() == 0) {
		return false;
	}

	if(_input->isKeyPressed(InputButton::KEYBOARD_RIGHT)) {
		++_activeScene;
	}
	if (_input->isKeyPressed(InputButton::KEYBOARD_LEFT)) {
		--_activeScene;
	}

	if (_activeScene >= (int)_scenes.size()) {
		_activeScene = 0;
	}
	else if (_activeScene < 0) {
		_activeScene = _scenes.size() - 1;
	}

	_scenes[_activeScene]->draw(delta);

	return true;
}
