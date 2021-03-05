#pragma once
struct Window {
	const char* title;
	int x;
	int y;
	int w;
	int h;
	Uint32 sdlFlags;
	bool vSync;
	int fpsLimit;
};