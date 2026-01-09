#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <Windows.h>

const auto KEYS_ARRAY_SIZE = 254;

struct KeyState
{
	BOOL wasPressed;
	BOOL isDown;
	BOOL wasReleased;
};

void keyboardHandler(DWORD key, WORD repeats, BYTE scanCode, BOOL isExtended, BOOL isWithAlt, BOOL wasDownBefore, BOOL isUpNow);
void resetKeyStates();

bool wasKeyPressed(DWORD key);
bool isKeyDown(DWORD key);
bool wasKeyReleased(DWORD key);
#endif // !KEYBOARD_H