#include "Engine.h"

constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 600;
constexpr int OPENGL_MAJOR_VERSION = 2;
constexpr int OPENGL_MINOR_VERSION = 1;
constexpr SDL_GLprofile OPENGL_PROFILE = SDL_GLprofile::SDL_GL_CONTEXT_PROFILE_CORE;

/**	\brief Initialize SDL

Since OpenGL needs a canvas to draw to, we use SDL to create a window. All necessary attributes of that window are initialized and set here.
\return true if initialization did not fail
*/
bool Engine::InitSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		//Error SDL_GetError();
		return false;
	}

	SDL_GL_SetAttribute(SDL_GL_SHARE_WITH_CURRENT_CONTEXT, 0);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, OPENGL_PROFILE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, OPENGL_MAJOR_VERSION);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, OPENGL_MINOR_VERSION);

	unsigned int Flags = SDL_WINDOW_OPENGL;
	Flags |= SDL_WINDOW_RESIZABLE;

	Window = SDL_CreateWindow(ManagedGame->GetWindowName().c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, Flags);
	if (Window == nullptr)return false;

	return true;
}

/**	\brief Initialize OpenGL

Here, an OpenGL context is created. Also, Glew, which is needed to call OpenGL functions, is initialized. Global OpenGL settings are initiated.
\return true if initialization did not fail
*/
bool Engine::InitOpenGL()
{
	GLContext = SDL_GL_CreateContext(Window);
	if (GLContext == nullptr)return false;

	const unsigned char *_version = glGetString(GL_VERSION);

	glewInit();
	SDL_GL_SetSwapInterval(0);
	glEnable(GL_CLIP_DISTANCE0);

	//GLint _maxTextures;
	//glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &_maxTextures);

	SDL_GL_MakeCurrent(Window, GLContext);

	glShadeModel(GL_SMOOTH);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	//glCullFace(GL_BACK);

	return true;
}

/** \brief The main game loop

Time measuremeent, handling inputs, rendering and updating the actual game take place here.
*/
void Engine::Loop()
{
	ManagedGame->Start();
	while (true)
	{
		clock_t start_time = clock(); // beginning to take the time needed to compute one frame
		if (ManagedGame->isStoped())return;
		auto frameData = GenerateFrameData();
		HandleEvents(frameData);
		ManagedGame->frameData = frameData;
		ManagedGame->Update();
		if (ManagedGame->isStoped())return;
		clock_t start_render_time = clock(); // beginning of the rendering process
		Render();
		clock_t end_time = clock(); // end of the time measurement.
		hardware::render_time(start_render_time, end_time);
		hardware::frames_per_second(start_time, end_time);

		std::cout << render_time_in_ms << " ms. \n"; // Temporary cout of render time
		std::cout << FPS << " FPS. \n";				// and FPS.
	}
}

/** \brief Renders the scene

This function renders the scene, which holds all lights, meshes etc.
Background color is reset and color as well as depth buffer are cleared. Also the window is swapped and therefore updated.
*/
void Engine::Render()
{
	glClearColor(0.2f, 0.2f, 0.2f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	auto scene = ManagedGame->GetScene();
	if (scene)scene->Draw();

	SDL_GL_SwapWindow(Window);
}

/** \brief Handles input events

This function handles the most important inputs. If events take place, they are passed so they can be used in the game.
\param aFrameData a shared pointer to a FrameData instance, which handles inputs further.
*/
void Engine::HandleEvents(shared_ptr<FrameData> aFrameData)
{
	SDL_Event _event;
	while (SDL_PollEvent(&_event) != 0)
	{
		switch (_event.type)
		{
		case SDL_WINDOWEVENT:
			switch (_event.window.event)
			{
			case SDL_WINDOWEVENT_CLOSE:
				aFrameData->windowCloseEvent = true;
				break;
			case SDL_WINDOWEVENT_LEAVE:
				MousePosition = nullptr;
				break;
			}
			break;
		case SDL_KEYDOWN:
			aFrameData->AddKeyDown(_event.key.keysym.sym);
			KeysPressed->insert(_event.key.keysym.sym);
			break;
		case SDL_KEYUP:
			aFrameData->AddKeyUp(_event.key.keysym.sym);
			KeysPressed->erase(_event.key.keysym.sym);
			break;
		case SDL_MOUSEBUTTONDOWN:
			//_event.button.button
			break;
		case SDL_MOUSEBUTTONUP:
			//_event.button.button
			break;
		case SDL_MOUSEMOTION:
			//_event.wheel.windowID
			MousePosition = make_shared<vec2>(float(_event.motion.x), float(_event.motion.y));
			break;
		case SDL_MOUSEWHEEL:
			//_event.wheel.windowID
			//_event.wheel.y
			break;
		case SDL_TEXTINPUT:
			//_event.wheel.windowID
			//_event.text.text
			break;
		}
	}
	aFrameData->MousePosition = MousePosition;
}

/** \brief Generate usefulk frame data

Frame data is generated. This means key input, the size of the actual window and the time between frames.
\return a shared pointer to the newly generated FrameData instance
*/
shared_ptr<FrameData> Engine::GenerateFrameData()
{
	auto ret = make_shared<FrameData>();
	auto newTimer = clock();
	auto deltaTime = newTimer - timer;
	timer = newTimer;
	ret->deltaTime = deltaTime / float(CLOCKS_PER_SEC);
	ret->SetKeyPressed(KeysPressed);
	int width;
	int height;
	SDL_GetWindowSize(Window, &width, &height);
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	ret->WindowSize = vec2(width, height);
	return ret;
}

/** \brief Starts the engine

This is the entry point of the class. The engine gets a Game instance and handles it according to the rules in that instance.
\param aGame a shared pointer to a Game instance
*/
void Engine::Start(shared_ptr<Game> aGame)
{
	if (!aGame)return;
	ManagedGame = aGame;
	if (!InitSDL())return;
	if (!InitOpenGL())return;
	Loop();
}