#pragma once
#include "core.h"
#include "Cube.h"
#include "Renderer.h"
#include "Window.h"

class Application {
public :
	
	
	void run();
	Application();
	~Application();

private:
	Renderer m_Renderer;
	Window window;
	void LoadImGui(myImGuiManager& myImGui);
	void processInput();
	float getRandom();

};