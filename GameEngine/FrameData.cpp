#include "FrameData.h"

/** \brief Check if key is down

This function checks KeysDown if it contains aKey.
\param aKey a key to check
\return true if key is down
*/
bool FrameData::IsKeyDown(SDL_Keycode aKey)
{
	return KeysDown.find(aKey) != KeysDown.end();
}

/** \brief Check if key is up

This function checks KeysUp if it contains aKey.
\param aKey a key to check
\return true if key is up
*/
bool FrameData::IsKeyUp(SDL_Keycode aKey)
{
	return KeysUp.find(aKey) != KeysUp.end();
}

/** \brief Check if key is pressed

This function checks KeysPressed if it contains aKey.
\param aKey a key to check
\return true if key is pressed
*/
bool FrameData::IsKeyPressed(SDL_Keycode aKey)
{
	return KeysPressed->find(aKey) != KeysPressed->end();
}

/** \brief Add key that is down

\param aKey a key to add to KeysDown
*/
void FrameData::AddKeyDown(SDL_Keycode aKey)
{
	KeysDown.insert(aKey);
}

/** \brief Add key that is up

\param aKey a key to add to KeysUp
*/
void FrameData::AddKeyUp(SDL_Keycode aKey)
{
	KeysUp.insert(aKey);
}

/** \brief Setter for KeysPressed

Assigns aKeysPressed to KeysPressed.
\param aKeysPressed the parameter to assign
*/
void FrameData::SetKeyPressed(shared_ptr<unordered_set<SDL_Keycode>> aKeysPressed)
{
	KeysPressed = aKeysPressed;
}

/** \brief Acquire mouse position

Returns mouse position.
\return a shared pointer to a vec2 which holds x and y coordinate of the mouse on the screen
*/
shared_ptr<vec2> FrameData::GetViewMousePosition()
{
	if (!MousePosition)return nullptr;
	return make_shared<vec2>(float((MousePosition->x / WindowSize.x)*2.0f - 1.0f), float(1.0f - (MousePosition->y / WindowSize.y)*2.0f));
}