#pragma once
#include <set>
#include <algorithm>
#include "InputButtons.h"

#include <Window/Window.h>

class Input
{
public:
	Input();
	~Input();

	void startup(Window* w);
	void update(float delta);
	void shutdown();

	bool isKeyPressed(InputButton key);
	bool isKeyHeld(InputButton key);
	bool isKeyReleased(InputButton key);

private:
	void setPressedButtons();
	void setReleasedButtons();
	void calculateHeldButtons();

	std::set<InputButton> pressed;
	std::set<InputButton> held;
	std::set<InputButton> released;

	std::set<InputButton> nextPressed;
	std::set<InputButton> nextReleased;

	std::function<void(int key, int scancode, int action, int mods)> getKeyEvent();

};

