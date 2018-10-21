#ifndef _FRAMEDATA_H
#define _FRAMEDATA_H

#include <unordered_set>
#include <memory>
#include <SDL_keycode.h>
using namespace std;

class FrameData
{
	unordered_set<SDL_Keycode> KeysDown;
	unordered_set<SDL_Keycode> KeysUp;
	shared_ptr<unordered_set<SDL_Keycode>> KeysPressed;
public:
	float deltaTime;
	bool windowCloseEvent;
	bool IsKeyDown(SDL_Keycode aKey);
	bool IsKeyUp(SDL_Keycode aKey);
	bool IsKeyPressed(SDL_Keycode aKey);
	void AddKeyDown(SDL_Keycode aKey);
	void AddKeyUp(SDL_Keycode aKey);
	void SetKeyPressed(shared_ptr<unordered_set<SDL_Keycode>> aKeysPressed);
};

#else
class FrameData;
#endif