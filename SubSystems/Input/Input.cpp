#include "Input.h"


Input::Input() 
{
}

Input::~Input()
{
}


std::function<void(int key, int scancode, int action, int mods)> Input::getKeyEvent()
{
	return [this](int key, int scancode, int action, int mods) {
		if (action == GLFW_PRESS) {
			nextPressed.emplace(InputButtonHelper::ConvertFromGLFW(key));
		}
		else if (action == GLFW_RELEASE) {
			nextReleased.emplace(InputButtonHelper::ConvertFromGLFW(key));
		}
	};
}

void Input::startup(Window* w)
{
	w->setInputCallback(getKeyEvent());
}

void Input::update(float delta)
{
	setPressedButtons();
	setReleasedButtons();
	calculateHeldButtons();
}

void Input::shutdown()
{
}

bool Input::isKeyPressed(InputButton key)
{
	return pressed.count(key);
}

bool Input::isKeyHeld(InputButton key)
{
	return held.count(key);
}

bool Input::isKeyReleased(InputButton key)
{
	return released.count(key);
}

void Input::setPressedButtons()
{
	pressed = nextPressed;
	nextPressed.clear();
}

void Input::setReleasedButtons()
{
	released = nextReleased;
	nextReleased.clear();
}

void Input::calculateHeldButtons()
{
	held.insert(pressed.begin(), pressed.end());
	for (auto key : released) {
		held.erase(key);
	}
}
