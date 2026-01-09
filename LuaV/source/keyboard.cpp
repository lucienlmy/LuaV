#include "keyboard.h"

KeyState keys[KEYS_ARRAY_SIZE] = {};

void keyboardHandler(DWORD key, WORD repeats, BYTE scanCode, BOOL isExtended, BOOL isWithAlt, BOOL wasDownBefore, BOOL isUpNow)
{
	if (key >= KEYS_ARRAY_SIZE)
	{
		return;
	}

	auto& state = keys[key];

	if (!wasDownBefore && !isUpNow)
	{
		state.wasPressed = TRUE;
		state.isDown = TRUE;
		state.wasReleased = FALSE;
	}
	else if (wasDownBefore && isUpNow)
	{
		state.wasPressed = FALSE;
		state.isDown = FALSE;
		state.wasReleased = TRUE;
	}
}

void resetKeyStates()
{
	for (int i = 0; i < KEYS_ARRAY_SIZE; ++i)
	{
		auto& state = keys[i];

		state.wasPressed = FALSE;
		state.wasReleased = FALSE;
	}
}

bool wasKeyPressed(DWORD key)
{
	return key < KEYS_ARRAY_SIZE && keys[key].wasPressed;
}

bool isKeyDown(DWORD key)
{
	return key < KEYS_ARRAY_SIZE && keys[key].isDown;
}

bool wasKeyReleased(DWORD key)
{
	return key < KEYS_ARRAY_SIZE && keys[key].wasReleased;
}