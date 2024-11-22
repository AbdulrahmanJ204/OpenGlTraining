#pragma once
#include "core.h"
#include "Renderer.h"
class Application {
private:
	Renderer m_Renderer;
	float m_MixValue = 0.2f;

public :
	static int m_Width , m_Height ;
	static GLFWwindow* window;

	Application();
	~Application();

private:

	void LoadImGui(myImGuiManager& myImGui);
	void processInput();
	
	float getRandom();
	int glfwIniti();
};