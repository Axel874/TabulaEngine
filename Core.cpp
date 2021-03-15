#include "pch.h"
#include "Core.h"
#include "Camera.h"
#include "Sprite.h"
#include "SpriteRenderer.h"
#include "Game.h"
#define LogWarning(message) LogWarning(message, __FILE__, __LINE__)

//public
Core::Core(const Window& windowProperties, const bool& debugMode)
	: m_Initialized(true), m_pSDLWindow(nullptr),m_Window(windowProperties), m_pCamera(nullptr) {
	Initialize();
	if (debugMode) { InitializeGLDebugCallback(); }
}
Core::~Core() {
	Terminate();
}

void Core::Run() {
	if (m_Initialized) {RunGameLoop();}
	else {utils::LogWarning("Unable to initialize core");}
}
//private
void Core::RunGameLoop()
{
	TimePoint t1 = Now(); //initial time stamp
	Game* pGame = new Game(); //run game init code
	SpriteRenderer renderer = SpriteRenderer(pGame->GetSprites()); //initialize sprite renderer
	m_pCamera = new Camera( //init camera (todo: move to game class and let the renderer read cam info)
		//also you should propably store quit info in the game class as that is the main processor of events
		//also add keyboards/mouse events processing to the game class
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f), 
		500.0f, glm::vec3(0.0f, 0.0f, -1.0f));
	//while HandleSDLEvents doese not return true (aka have to quit), run game loop
	while (!HandleSDLEvents()) {
		TimePoint t2 = Now();
		float deltaTime = GetTimeDiff(t2, t1);
		const bool isTimeToRender = deltaTime > (1.0f / m_Window.fpsLimit);
		if (isTimeToRender) {
			HandleUserInput(deltaTime);
			//update last frame rendered timestamp
			t1 = t2;
			//update game
			pGame->Update(deltaTime);
			//render sprites
			renderer.RenderSprites(m_pCamera->GetViewMatrix(), m_pSDLWindow);
		}
	}
	delete pGame;
}
void Core::HandleUserInput(float deltaTime)
{
	ProcessKeyStates(deltaTime);
	ProcessMouseMovement();
}
void Core::ProcessMouseMovement()
{
}
void Core::ProcessKeyStates(float& deltaTime)
{
	const Uint8* keyStates = SDL_GetKeyboardState(NULL);
	if (keyStates[SDL_SCANCODE_W])m_pCamera->ProcessKeyState(CameraMovement::UPWARDS, deltaTime);
	if (keyStates[SDL_SCANCODE_S])m_pCamera->ProcessKeyState(CameraMovement::DOWNWARDS, deltaTime);
	if (keyStates[SDL_SCANCODE_A])m_pCamera->ProcessKeyState(CameraMovement::LEFT, deltaTime);
	if (keyStates[SDL_SCANCODE_D])m_pCamera->ProcessKeyState(CameraMovement::RIGHT, deltaTime);

}
bool Core::HandleSDLEvents()
{
	SDL_Event event{};
	while (SDL_PollEvent(&event)) {

		switch (event.type) {
		case SDL_QUIT:
			return true;
			break;
		case SDL_WINDOWEVENT:
			if (event.window.event == SDL_WINDOWEVENT_RESIZED)ResizeGLViewport();
			break;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE) {
					SDL_Event quitEvent;
					quitEvent.type = SDL_QUIT;
					quitEvent.quit.timestamp = SDL_GetTicks();
					SDL_PushEvent(&quitEvent);
			}
		}
	}
	return false;
}

void Core::Initialize() {
	if (m_Initialized)InitSDL();
	if (m_Initialized)InitSDLWindow();
	if (m_Initialized)SDL_GL_CreateContext(m_pSDLWindow);
	if (m_Initialized)InitSDLMouse();
	if (m_Initialized)InitGLAD();
	if (m_Initialized)InitGL();
}
void Core::InitSDLMouse()
{
	SDL_SetRelativeMouseMode(SDL_TRUE);
	SDL_CaptureMouse(SDL_TRUE);
}
void Core::InitGLAD() {
	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		m_Initialized = false;
	}
}
void Core::InitSDL()
{
	const int errorCode = SDL_Init(SDL_INIT_VIDEO);
	if (errorCode != 0) {
		std::string warningMessage = "Error ";
		warningMessage += std::to_string(errorCode);
		warningMessage += ", failed loading sdl";

		utils::LogWarning(warningMessage);
		m_Initialized = false;
	}
	else {
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	}
}
void Core::InitSDLWindow()
{
	Window& w = m_Window;
	m_pSDLWindow = SDL_CreateWindow(w.title, w.x, w.y, w.w, w.h, w.sdlFlags);
	if (m_pSDLWindow == nullptr) {
		utils::LogWarning("failed creating sdl window");
		m_Initialized = false;
	}

}
void Core::InitGL() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
}
void Core::InitializeGLDebugCallback()
{
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(MessageCallback, 0);
}

void Core::Terminate() {
	if (SDL_GL_GetCurrentContext() != NULL) 
		SDL_GL_DeleteContext(SDL_GL_GetCurrentContext());
	if (m_pSDLWindow != nullptr)
		SDL_DestroyWindow(m_pSDLWindow);
	if (m_pCamera != nullptr)delete m_pCamera;
	SDL_Quit();
}

void Core::ResizeGLViewport()
{
	int h, w;
	SDL_GetWindowSize(m_pSDLWindow, &w, &h);
	m_Window.w = w;
	m_Window.h = h;
	glViewport(0, 0, w, h);
}
TimePoint Core::Now() {
	return std::chrono::steady_clock::now();
}
float Core::GetTimeDiff(TimePoint& t2, TimePoint& t1)
{
	return std::chrono::duration<float>(t2 - t1).count();
}
void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id,
	GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
	fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
		(type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
		type, severity, message);
}