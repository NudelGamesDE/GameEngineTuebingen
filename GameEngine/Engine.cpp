#include "Engine.h"

constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 600;
constexpr int OPENGL_MAJOR_VERSION = 2;
constexpr int OPENGL_MINOR_VERSION = 1;
constexpr SDL_GLprofile OPENGL_PROFILE = SDL_GLprofile::SDL_GL_CONTEXT_PROFILE_CORE;

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

void Engine::Loop()
{
	while (true)
	{
		if (ManagedGame->isStoped())return;
		ManagedGame->Update();
		if (ManagedGame->isStoped())return;
		Render();
	}
}


void Engine::Render()
{
	glClearColor(0.2f, 0.2f, 0.2f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	auto scene = ManagedGame->GetScene();
	if (scene)scene->Draw();

	SDL_GL_SwapWindow(Window);
}


void Engine::Start(Game_ptr aGame)
{
	if (!aGame)return;
	ManagedGame = aGame;
	if (!InitSDL())return;
	if (!InitOpenGL())return;
	Loop();
}