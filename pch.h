#ifndef PCH_H
#define PCH_H
// SDL libs
#pragma comment(lib, "sdl2.lib")
#pragma comment(lib, "SDL2main.lib")
// OpenGL libs
#pragma comment (lib,"opengl32.lib")

//sdl/gl/glad headers
#include <glad.h>
#pragma warning (push)
#pragma warning(disable : 26812)
#include <SDL.h>
#pragma warning (pop)
#include <SDL_opengl.h>

//GLM headers
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

//stb_image loader
#pragma warning (push)
#pragma warning(disable : 26451 6011 6262 6308 28182 6262)
#include "stb_image.h"
#pragma warning (pop)

//c++ headers
#include <iostream>
#include <string>
#include <chrono>
#include <fstream>

//my headers
#include "Window.h"
#include "Utils.h"
#endif //PCH_H
