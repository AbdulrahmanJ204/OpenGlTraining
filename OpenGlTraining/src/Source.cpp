
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
#include <tests/TestClearColor.h>

int width = 800, height = 800;
float getRandom() {
	return (float)(rand() % 100) / 100;
}



int glfwIniti(GLFWwindow*& window) {
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	window = glfwCreateWindow(width, height, "OPEN GL", NULL, NULL);

	if (window == NULL) {
		spdlog::error("Failed to create GLFW window");
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	// glad: load all OpenGL function pointers
// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		spdlog::error("Failed to initialize GLAD");
		return -1;
	}
	return 0;
}

int main() {
	//srand(time(0));
	spdlog::info("Starting Application");
	GLFWwindow* window;
	int returnValue = glfwIniti(window);
	if (returnValue) {
		return returnValue;
	}

	Renderer renderer;

	test::Test* currentTest = nullptr;
	test::TestMenu* testsMenu = new test::TestMenu(currentTest);
	currentTest = testsMenu;
	testsMenu->AddTest<test::TestClearColor>("Clear Color");

	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	myImGuiManager myImGui(window , width , height);
	while (!glfwWindowShouldClose(window)) {
		renderer.Clear();
		GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		myImGui.BeginFrame();
		
		
		glfwPollEvents();
		
		
		if (currentTest) {
			currentTest->OnUpdate(0.0f);
			currentTest->OnRender();
			ImGui::Begin("Test");
			if (currentTest != testsMenu && ImGui::Button("<-")) {
				delete	currentTest;
				currentTest = testsMenu;
			}
			currentTest->OnImGuiRender();
			ImGui::End();
		}
		

		myImGui.EndFrame();
		
		glfwSwapBuffers(window);
	}

	delete testsMenu;
	if (testsMenu != currentTest) {
		delete currentTest;
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}










//float vertices1[] = {
//	-0.8f, -0.4f , 0.1f,      1.0f , 0.0f, 0.3f , 1.0f,
//	 -0.01f, -0.4f ,0.1f,    0.0f, 1.0f, 0.0f , 1.0f,
//	 -0.01f, 0.8f , 0.1f,     0.0f, 0.0f , 1.0f ,1.0f
//};

//float vertices1[] = {
	//	-0.95f, -0.95f, 0.0f , 0.0f, 1.0f , 1.0f,
	//	 0.95f, 0.0f, 0.0f, 0.0f, 1.0f , 1.0f,
	//	 -0.95f, 0.95f,  0.0f, 0.0f , 1.0f ,1.0f
	//};
	// 
	//float vertices2[] = {
	//	 -0.4f , -0.4f,	0.0f,	 1.0f , 0.5f, 0.3f , 1.0f,
	//	 0.8f , -0.4f,0.0f,	0.5f, 0.3f , 1.0f ,1.0f,
	//	 0.01f , 0.4f,	0.0f,	 0.5f, 1.0f, 0.3f , 1.0f
	//};