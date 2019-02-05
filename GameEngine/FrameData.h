#ifndef _FRAMEDATA_H
#define _FRAMEDATA_H

#include <unordered_set>
#include <memory>
#include <SDL_keycode.h>
#include <glm\vec2.hpp>
using namespace std;
using namespace glm;

/** \brief A frame data class

This frame data class is a container class for all kinds of useful information.
This includes the time between frames, mouse position, which key is pressed and the window size.
*/
class FrameData
{
	unordered_set<SDL_Keycode> KeysDown;
	unordered_set<SDL_Keycode> KeysUp;
	shared_ptr<unordered_set<SDL_Keycode>> KeysPressed;
public:
	float deltaTime;
	bool windowCloseEvent;
	shared_ptr<vec2> MousePosition;
	vec2 WindowSize;
	bool IsKeyDown(SDL_Keycode aKey);
	bool IsKeyUp(SDL_Keycode aKey);
	bool IsKeyPressed(SDL_Keycode aKey);
	void AddKeyDown(SDL_Keycode aKey);
	void AddKeyUp(SDL_Keycode aKey);
	void SetKeyPressed(shared_ptr<unordered_set<SDL_Keycode>> aKeysPressed);
	shared_ptr<vec2> GetViewMousePosition();
};

#else
class FrameData;
#endif