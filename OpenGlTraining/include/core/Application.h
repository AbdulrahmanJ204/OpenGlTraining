#pragma once
#include "core.h"
#include "Cube.h"
#include "Renderer.h"
#include "Window.h"
#include "Camera.h"
#include "Scene.h"
class Application {
public :
	
	
	void run();
	Application();
	~Application();
	static Application& instance() { return *instancePtr; };
	Window& getWindow() { return window; };

	void onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode);
	void onCursorPositionEvent(double x, double y);
	static Application* instancePtr;
private:
	Renderer m_Renderer;
	Window window;
	
	Scene scene;
	float lastX  , lastY;
	bool firstMouse = true;
	myImGuiManager myImGui;
	// timing
	float deltaTime = 0.0f;	// time between current frame and last frame
	float lastFrame = 0.0f;

	void LoadImGui();
	float movementSpeedMultiplier = 1;
	float mouseSensitivity = .5;


	
	void processInput();
	float getRandom();

};