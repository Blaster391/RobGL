#pragma once
#include <External/glfw/glfw3.h>

enum class InputButton {
	KEYBOARD_A,
	KEYBOARD_B,
	KEYBOARD_C,
	KEYBOARD_D,
	KEYBOARD_E,
	KEYBOARD_F,
	KEYBOARD_G,
	KEYBOARD_H,
	KEYBOARD_I,
	KEYBOARD_J,
	KEYBOARD_K,
	KEYBOARD_L,
	KEYBOARD_M,
	KEYBOARD_N,
	KEYBOARD_O,
	KEYBOARD_P,
	KEYBOARD_Q,
	KEYBOARD_R,
	KEYBOARD_S,
	KEYBOARD_T,
	KEYBOARD_U,
	KEYBOARD_V,
	KEYBOARD_W,
	KEYBOARD_X,
	KEYBOARD_Y,
	KEYBOARD_Z,

	KEYBOARD_SPACE,
	KEYBOARD_L_SHIFT,
	KEYBOARD_L_CTRL,

	KEYBOARD_LEFT,
	KEYBOARD_RIGHT,
	KEYBOARD_UP,
	KEYBOARD_DOWN,

	KEYBOARD_ESCAPE,

	MOUSE_0, 
	MOUSE_1,
	MOUSE_2,

	UNKNOWN
};

class InputButtonHelper {
public:
	static InputButton ConvertFromGLFW(int key) {
		switch (key) {
		case GLFW_KEY_A :
			return InputButton::KEYBOARD_A;
		case GLFW_KEY_B:
			return InputButton::KEYBOARD_B;
		case GLFW_KEY_C:
			return InputButton::KEYBOARD_C;
		case GLFW_KEY_D:
			return InputButton::KEYBOARD_D;
		case GLFW_KEY_E:
			return InputButton::KEYBOARD_E;
		case GLFW_KEY_F:
			return InputButton::KEYBOARD_F;
		case GLFW_KEY_G:
			return InputButton::KEYBOARD_G;
		case GLFW_KEY_H:
			return InputButton::KEYBOARD_H;
		case GLFW_KEY_I:
			return InputButton::KEYBOARD_I;
		case GLFW_KEY_J:
			return InputButton::KEYBOARD_J;
		case GLFW_KEY_K:
			return InputButton::KEYBOARD_K;
		case GLFW_KEY_L:
			return InputButton::KEYBOARD_L;
		case GLFW_KEY_M:
			return InputButton::KEYBOARD_M;
		case GLFW_KEY_N:
			return InputButton::KEYBOARD_N;
		case GLFW_KEY_O:
			return InputButton::KEYBOARD_O;
		case GLFW_KEY_P:
			return InputButton::KEYBOARD_P;
		case GLFW_KEY_Q:
			return InputButton::KEYBOARD_Q;
		case GLFW_KEY_R:
			return InputButton::KEYBOARD_R;
		case GLFW_KEY_S:
			return InputButton::KEYBOARD_S;
		case GLFW_KEY_T:
			return InputButton::KEYBOARD_T;
		case GLFW_KEY_U:
			return InputButton::KEYBOARD_U;
		case GLFW_KEY_V:
			return InputButton::KEYBOARD_V;
		case GLFW_KEY_W:
			return InputButton::KEYBOARD_W;
		case GLFW_KEY_X:
			return InputButton::KEYBOARD_X;
		case GLFW_KEY_Y:
			return InputButton::KEYBOARD_Y;
		case GLFW_KEY_Z:
			return InputButton::KEYBOARD_Z;
		case GLFW_KEY_LEFT:
			return InputButton::KEYBOARD_LEFT;
		case GLFW_KEY_RIGHT:
			return InputButton::KEYBOARD_RIGHT;
		case GLFW_KEY_UP:
			return InputButton::KEYBOARD_UP;
		case GLFW_KEY_DOWN:
			return InputButton::KEYBOARD_DOWN;

		case GLFW_KEY_SPACE:
			return InputButton::KEYBOARD_SPACE;
		case GLFW_KEY_LEFT_SHIFT:
			return InputButton::KEYBOARD_L_SHIFT;
		case GLFW_KEY_LEFT_CONTROL:
			return InputButton::KEYBOARD_L_CTRL;
		case GLFW_KEY_ESCAPE:
			return InputButton::KEYBOARD_ESCAPE;
		}
		return InputButton::UNKNOWN;
	}
};