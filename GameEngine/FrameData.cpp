#include "FrameData.h"

bool FrameData::IsKeyDown(SDL_Keycode aKey)
{
	return KeysDown.find(aKey) != KeysDown.end();
}

bool FrameData::IsKeyUp(SDL_Keycode aKey)
{
	return KeysUp.find(aKey) != KeysUp.end();
}

bool FrameData::IsKeyPressed(SDL_Keycode aKey)
{
	return KeysPressed->find(aKey) != KeysPressed->end();
}

void FrameData::AddKeyDown(SDL_Keycode aKey)
{
	KeysDown.insert(aKey);
}

void FrameData::AddKeyUp(SDL_Keycode aKey)
{
	KeysUp.insert(aKey);
}

void FrameData::SetKeyPressed(shared_ptr<unordered_set<SDL_Keycode>> aKeysPressed)
{
	KeysPressed = aKeysPressed;
}

shared_ptr<vec2> FrameData::GetViewMousePosition()
{
	if (!MousePosition)return nullptr;
	return make_shared<vec2>(float((MousePosition->x / WindowSize.x)*2.0f - 1.0f), float(1.0f - (MousePosition->y / WindowSize.y)*2.0f));
}