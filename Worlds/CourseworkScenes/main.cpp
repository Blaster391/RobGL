#include "ValleyScene.h"
#include "SpaceScene.h"

#include "SceneManager.h"
#include <Input/Input.h>
#include <Window/Window.h>
#include "Timer.h"

int main() {

	Window window;
	window.startup();

	Input input;
	input.startup(&window);

	//Setup scene manager
	SceneManager sceneManager(&input);
	ValleyScene valleyScene(window);
	SpaceScene spaceScene(window);

	sceneManager.addScene(&valleyScene);
	sceneManager.addScene(&spaceScene);

	//Setup window
	window.hideCursor();

	//Setup resize callbacks
	auto resizeCallback = [&](int width, int height) {
		sceneManager.onResize(width, height);
	};
	window.setWindowResizeCallback(resizeCallback);

	bool windowed = false;

	Timer _frameTimer;
	_frameTimer.start();

	bool finished = false;

	while (!finished) {
		float delta = _frameTimer.delta();

		input.update(delta);

		if (!sceneManager.update(delta)) {
			finished = true;
		}
		if (window.ShouldClose()) {
			finished = true;
		}


		if (input.isKeyPressed(InputButton::KEYBOARD_O)) {
			windowed = !windowed;
			if (windowed) {
				window.setWindowedMode();
			}
			else {
				window.setFullScreen();
			}
		}
	}

	input.shutdown();
	window.shutdown();

	return 0;
}