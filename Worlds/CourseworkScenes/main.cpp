#include "ValleyScene.h"
#include "SpaceScene.h"
#include "AbductionScene.h"

#include "SceneManager.h"
#include <Input/Input.h>
#include <Window/Window.h>
#include "Timer.h"

#include "AssetPack.h"

int main() {

	Window window;
	window.startup();

	Input input;
	input.startup(&window);

	//Setup scene manager
	SceneManager sceneManager(&input);
	ValleyScene valleyScene(window, input);
	SpaceScene spaceScene(window, input);
	AbductionScene abductionScene(window, input);

	AssetPack assets;
	assets.loadSharedResources();

	assets.loadValleyResources();
	assets.loadSpaceResources();
	assets.loadAbductionResources();

	valleyScene.setup(&assets);
	spaceScene.setup(&assets);
	abductionScene.setup(&assets);

	sceneManager.addScene(&spaceScene);
	sceneManager.addScene(&abductionScene);
	sceneManager.addScene(&valleyScene);

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

		window.update(delta);

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


		if (input.isKeyPressed(InputButton::KEYBOARD_ESCAPE)) {
			finished = true;
		}
	}

	input.shutdown();
	window.shutdown();

	return 0;
}