#include "pch.h"
#include "Core.h"
#include "ProgramShader.h"
#include "Texture.h"
#include "Camera.h"
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

	float vertices[] = {
		// positions          // normals           // texture coords
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
	};
	unsigned int indices[] = {
	 0, 1, 3, // first triangle
	 1, 2, 3  // second triangle
	};

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	GLuint VBO{};
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	GLuint EBO{};
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3* sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);


	glBindVertexArray(VAO);

	//texture loading
	Texture boxDiffuseTexture = Texture("./resources/images/boxDiffuse.png", GL_RGBA);
	Texture boxSpecularTexture = Texture("./resources/images/boxSpecular.png", GL_RGBA);
	boxDiffuseTexture.Bind(GL_TEXTURE0);
	boxSpecularTexture.Bind(GL_TEXTURE1);

	ProgramShader shader = ProgramShader("./resources/shaders/base");
	shader.Bind();
	shader.setInt("material.diffuseTexture", 0);
	shader.setInt("material.specularTexture", 1);
	shader.setFloat("material.shininess", 64.0f);

	shader.setVector3f("light.ambientFactor", glm::vec3(0.2f, 0.2f, 0.2f));
	shader.setVector3f("light.diffuseFactor", glm::vec3(1.0f, 1.0f, 1.0f));
	shader.setVector3f("light.specularFactor", glm::vec3(1.0f, 1.0f, 1.0f));
	ProgramShader lightShader = ProgramShader("./resources/shaders/light");

	m_LightColor = glm::vec3(1.0f, 1.0f, 1.0f);
	m_LightPosition = glm::vec3(5.0f, 5.0f, 0.0f);

	m_pCamera = new Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 5.0f, 0.2f);


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
			glm::mat4 projection = glm::perspective(glm::radians(45.0f), float(m_Window.w) / float(m_Window.w), 0.1f, 100.0f);
			glm::mat4 model = glm::mat4(1.0f);

			m_LightPosition.x = 5*sin(SDL_GetTicks()/1000.0f);
			m_LightPosition.y = 5*cos(SDL_GetTicks()/1000.0f);

			shader.Bind();
			shader.setMatrix4fv("view", view);
			shader.setMatrix4fv("projection", projection);

			shader.setVector3f("camPos", m_pCamera->GetPosition());
			shader.setVector3f("light.position", m_LightPosition);
			

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			//draw objects
			for (int i = 0; i < 2; i++) {
				model = glm::translate(model, glm::vec3(i * 2, 0, 0));
				model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(0.2f, 0.8f, 0.6f));
				shader.setMatrix4fv("model", model);
				glDrawArrays(GL_TRIANGLES, 0, 36);
			}

			////draw lights
			lightShader.Bind();
			lightShader.setVector3f("lightColor", glm::vec3(0.5f, 0.5f, 0.5f));
			lightShader.setMatrix4fv("view", view);
			lightShader.setMatrix4fv("projection", projection);
			model = glm::mat4(1.0f);
			model = glm::translate(model, m_LightPosition);
			lightShader.setMatrix4fv("model", model);
			glDrawArrays(GL_TRIANGLES, 0, 36);
			std::cout << "ambient: " << m_AmbientStrength << ";specular: " << m_SpecularStrength << ";specularc: " << m_SpecularConcentration << std::endl;
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
	int xpos, ypos;
	SDL_GetMouseState(&xpos, &ypos);
	if (firstMouse)
	{
		lastX = float(xpos);
		lastY = float(ypos);
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
	lastX = float(xpos);
	lastY = float(ypos);

	m_pCamera->ProcessMouseMovement(xoffset, yoffset, true);
}
void Core::ProcessKeyStates(float& deltaTime)
{
	const Uint8* keyStates = SDL_GetKeyboardState(NULL);
	if (keyStates[SDL_SCANCODE_W])m_pCamera->ProcessKeyState(CameraMovement::FORWARDS, deltaTime);
	if (keyStates[SDL_SCANCODE_S])m_pCamera->ProcessKeyState(CameraMovement::BACKWARDS, deltaTime);
	if (keyStates[SDL_SCANCODE_A])m_pCamera->ProcessKeyState(CameraMovement::LEFT, deltaTime);
	if (keyStates[SDL_SCANCODE_D])m_pCamera->ProcessKeyState(CameraMovement::RIGHT, deltaTime);
	//if (keyStates[SDL_SCANCODE_UP] && m_LightColor.x < 1.0f) m_LightColor += glm::vec3(0.01f);
	//if (keyStates[SDL_SCANCODE_DOWN] && m_LightColor.x > 0.0f) m_LightColor -= glm::vec3(0.01f);
	if (keyStates[SDL_SCANCODE_O]) m_SpecularConcentration += 1;
	if (keyStates[SDL_SCANCODE_L]) m_SpecularConcentration -= 1;
	if (keyStates[SDL_SCANCODE_P] && m_SpecularStrength < 1.0f) m_SpecularStrength += 0.01f;
	if (keyStates[SDL_GetScancodeFromKey(SDLK_m)] && m_SpecularStrength > 0.0f) m_SpecularStrength -= 0.01f;
	if (keyStates[SDL_SCANCODE_I] && m_AmbientStrength < 1.0f) m_AmbientStrength += 0.01f;
	if (keyStates[SDL_SCANCODE_K] && m_AmbientStrength > 0.0f) m_AmbientStrength -= 0.01f;

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