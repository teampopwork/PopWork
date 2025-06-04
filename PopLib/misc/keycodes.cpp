#include "keycodes.hpp"

using namespace PopLib;

#define MAX_KEYNAME_LEN 12

typedef struct
{
	SDL_Keycode mSDLKey;
	KeyCode mKeyCode;
} KeyNameEntry;

KeyNameEntry aKeyCodeArray[] = {{SDLK_UNKNOWN, KEYCODE_UNKNOWN},
								{SDLK_CANCEL, KEYCODE_CANCEL},
								{SDLK_BACKSPACE, KEYCODE_BACK},
								{SDLK_TAB, KEYCODE_TAB},
								{SDLK_CLEAR, KEYCODE_CLEAR},
								{SDLK_RETURN, KEYCODE_RETURN},
								{SDLK_LSHIFT, KEYCODE_SHIFT},
								{SDLK_RSHIFT, KEYCODE_SHIFT},
								{SDLK_LCTRL, KEYCODE_CONTROL},
								{SDLK_RCTRL, KEYCODE_CONTROL},
								{SDLK_MENU, KEYCODE_MENU},
								{SDLK_PAUSE, KEYCODE_PAUSE},
								{SDLK_CAPSLOCK, KEYCODE_CAPITAL},
								{SDLK_ESCAPE, KEYCODE_ESCAPE},
								{SDLK_SPACE, KEYCODE_SPACE},
								{SDLK_PAGEUP, KEYCODE_PAGEUP},
								{SDLK_PAGEDOWN, KEYCODE_PAGEDOWN},
								{SDLK_END, KEYCODE_END},
								{SDLK_HOME, KEYCODE_HOME},
								{SDLK_LEFT, KEYCODE_LEFT},
								{SDLK_UP, KEYCODE_UP},
								{SDLK_RIGHT, KEYCODE_RIGHT},
								{SDLK_DOWN, KEYCODE_DOWN},
								{SDLK_SELECT, KEYCODE_SELECT},
								{SDLK_EXECUTE, KEYCODE_EXECUTE},
								{SDLK_PRINTSCREEN, KEYCODE_SNAPSHOT},
								{SDLK_INSERT, KEYCODE_INSERT},
								{SDLK_DELETE, KEYCODE_DELETE},
								{SDLK_HELP, KEYCODE_HELP},
								{SDLK_LGUI, KEYCODE_LWIN},
								{SDLK_RGUI, KEYCODE_RWIN},
								{SDLK_APPLICATION, KEYCODE_APPS},
								{SDLK_KP_0, KEYCODE_NUMPAD0},
								{SDLK_KP_1, KEYCODE_NUMPAD1},
								{SDLK_KP_2, KEYCODE_NUMPAD2},
								{SDLK_KP_3, KEYCODE_NUMPAD3},
								{SDLK_KP_4, KEYCODE_NUMPAD4},
								{SDLK_KP_5, KEYCODE_NUMPAD5},
								{SDLK_KP_6, KEYCODE_NUMPAD6},
								{SDLK_KP_7, KEYCODE_NUMPAD7},
								{SDLK_KP_8, KEYCODE_NUMPAD8},
								{SDLK_KP_9, KEYCODE_NUMPAD9},
								{SDLK_KP_MULTIPLY, KEYCODE_MULTIPLY},
								{SDLK_KP_PLUS, KEYCODE_ADD},
								{SDLK_KP_DECIMAL, KEYCODE_SEPARATOR},
								{SDLK_KP_MINUS, KEYCODE_SUBTRACT},
								{SDLK_KP_DECIMAL, KEYCODE_DECIMAL},
								{SDLK_KP_DIVIDE, KEYCODE_DIVIDE},
								{SDLK_F1, KEYCODE_F1},
								{SDLK_F2, KEYCODE_F2},
								{SDLK_F3, KEYCODE_F3},
								{SDLK_F4, KEYCODE_F4},
								{SDLK_F5, KEYCODE_F5},
								{SDLK_F6, KEYCODE_F6},
								{SDLK_F7, KEYCODE_F7},
								{SDLK_F8, KEYCODE_F8},
								{SDLK_F9, KEYCODE_F9},
								{SDLK_F10, KEYCODE_F10},
								{SDLK_F11, KEYCODE_F11},
								{SDLK_F12, KEYCODE_F12},
								{SDLK_F13, KEYCODE_F13},
								{SDLK_F14, KEYCODE_F14},
								{SDLK_F15, KEYCODE_F15},
								{SDLK_F16, KEYCODE_F16},
								{SDLK_F17, KEYCODE_F17},
								{SDLK_F18, KEYCODE_F18},
								{SDLK_F19, KEYCODE_F19},
								{SDLK_F20, KEYCODE_F20},
								{SDLK_F21, KEYCODE_F21},
								{SDLK_F22, KEYCODE_F22},
								{SDLK_F23, KEYCODE_F23},
								{SDLK_F24, KEYCODE_F24},
								{SDLK_NUMLOCKCLEAR, KEYCODE_NUMLOCK},
								{SDLK_SCROLLLOCK, KEYCODE_SCROLL}};

KeyCode PopLib::GetKeyCodeFromSDLKeycode(const SDL_Keycode key)
{
	return GetKeyCodeFromName(SDL_GetKeyName(key));
}

KeyCode PopLib::GetKeyCodeFromName(const std::string &theKeyName)
{
	if (theKeyName.length() >= MAX_KEYNAME_LEN - 1)
		return KEYCODE_UNKNOWN;

	if (theKeyName.length() == 1)
	{
		unsigned char aKeyNameChar = theKeyName[0];

		if ((aKeyNameChar >= KEYCODE_ASCIIBEGIN) && (aKeyNameChar <= KEYCODE_ASCIIEND))
			return (KeyCode)aKeyNameChar;
	}

	for (int i = 0; i < sizeof(aKeyCodeArray) / sizeof(aKeyCodeArray[0]); i++)
		if (strcmp(theKeyName.c_str(), SDL_GetKeyName(aKeyCodeArray[i].mSDLKey)) == 0)
			return aKeyCodeArray[i].mKeyCode;

	return KEYCODE_UNKNOWN;
}

const std::string PopLib::GetKeyNameFromCode(const KeyCode &theKeyCode)
{
	if ((theKeyCode >= KEYCODE_ASCIIBEGIN) && (theKeyCode <= KEYCODE_ASCIIEND))
	{
		char aStr[2] = {(char)theKeyCode, 0};
		return aStr;
	}

	for (int i = 0; i < sizeof(aKeyCodeArray) / sizeof(aKeyCodeArray[0]); i++)
		if (theKeyCode == aKeyCodeArray[i].mKeyCode)
			return SDL_GetKeyName(aKeyCodeArray[i].mSDLKey);

	return "UNKNOWN";
}