#pragma once

#include<iostream>
#include<spdlog/spdlog.h>

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>	
#include<glm/gtc/matrix_transform.hpp>


#include"GLErrorManager.h"
#include"VertexBuffer.h"
#include"IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Renderer.h"
#include "Texture.h"

#include "imGui/imgui.h"
#include "imGui/imgui_impl_glfw.h"
#include "imGui/imgui_impl_opengl3.h"
#include "myImGuiManager.h"
#include "tests/TestClearColor.h"
#include "tests/TestTexture2D.h"
class Application {
	GLFWwindow* window;
	Renderer m_Renderer;
	float m_MixValue = 0.2f;
	test::Test* m_CurrentTest = nullptr;
	test::TestMenu* m_TestsMenu = nullptr;
	int m_Width = 800, m_Height = 800;
public:

	Application();
	~Application();

private:

	void LoadImGui(myImGuiManager& myImGui);
	float getRandom();
	int glfwIniti();
	void processInput();
};