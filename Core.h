#pragma once
struct Window;
struct SDL_Window;
class Camera;
void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id,
	GLenum severity, GLsizei length, const GLchar* message, const void* userParam);

typedef std::chrono::steady_clock::time_point TimePoint;
class Core {
public:
	Core(const Window& windowProperties, const bool& debugMode);
	~Core();

	void Run();
private:
	Window m_Window;
	SDL_Window* m_pSDLWindow;
	bool m_Initialized;

	bool firstMouse = true;
	float lastX = 800.0f / 2.0;
	float lastY = 600.0 / 2.0;

	Camera* m_pCamera;
	glm::vec3 m_LightColor;
	glm::vec3 m_LightPosition;
	float m_AmbientStrength, m_SpecularStrength, m_SpecularConcentration;

	void Initialize();
	void InitSDLMouse();
	void InitGLAD();
	void InitSDL();
	void InitSDLWindow();
	void InitGL();
	void InitializeGLDebugCallback();


	void Terminate();

	void RunGameLoop();
	bool HandleSDLEvents();
	void HandleUserInput(float deltaTime);
	void ProcessMouseMovement();
	void ProcessKeyStates(float& deltaTime);

	void ResizeGLViewport();
	TimePoint Now();
	float GetTimeDiff(TimePoint& t2, TimePoint& t1);
};