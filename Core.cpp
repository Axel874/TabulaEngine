#include "pch.h"
#include "Core.h"
#include "ProgramShader.h"
#include "Texture.h"
#include "Camera.h"
#include "Sprite.h"

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

	Sprite box = Sprite("./resources/images/boxDiffuse.png", glm::vec3(0, 0, 0), glm::vec2(100, 100));

	//create vertex array object and bind it
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//create data buffer
	GLuint VBO{};
	glGenBuffers(1, &VBO);
	//bind data buffer to vertex array object
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//push vertex data to buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*24, box.GetVertexData(), GL_STATIC_DRAW);
	//set info about where to find 1st attribute of our data
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//idem for 2d attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2* sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);

	//texture loading
	Texture boxDiffuseTexture = Texture(box.GetSource(), GL_RGBA);
	//bind to texture unit 1/16
	boxDiffuseTexture.Bind(GL_TEXTURE0);

	//load base shader program
	ProgramShader shader = ProgramShader("./resources/shaders/base");
	//bind the shader for use
	shader.setInt("ourTexture", 0);

	m_pCamera = new Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 500.0f, glm::vec3(0.0f, 0.0f, -1.0f));
	//while HandleSDLEvents doese not return true (aka have to quit), run game loop
	while (!HandleSDLEvents()) {
		TimePoint t2 = Now();
		float deltaTime = GetTimeDiff(t2, t1);
		const bool isTimeToRender = deltaTime > (1.0f / m_Window.fpsLimit);
		if (isTimeToRender) {
			HandleUserInput(deltaTime);
			//update time tracker
			t1 = t2;
			//update game
			glm::mat4 view = m_pCamera->GetViewMatrix();
			glm::mat4 projectionOrtho = glm::ortho(0.f, 500.0f, 0.f, 280.f, 5.0f, -5.0f);
			glm::mat4 model = glm::mat4(1.0f);


			shader.setMatrix4fv("view", view);
			shader.setMatrix4fv("projection", projectionOrtho);

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			//draw objects
			//model = glm::translate(model, glm::vec3(i * 2, 0, 0));
			//model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(0.2f, 0.8f, 0.6f));
			shader.setMatrix4fv("model", model);


			shader.Bind();
			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLES, 0, 6);
			//swap drawn buffer with render buffer
			SDL_GL_SwapWindow(m_pSDLWindow);
		}

	}
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