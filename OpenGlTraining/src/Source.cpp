
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

	

	//-----------------------------------------------------------------------------------------------------
	float verticies[] = {
		// position			   color						textures
		0.0f   , 0.0f   ,0.0f, 1.0f, 0.0f, 0.0f, 1.0f,	0.0f , 0.0f ,
		400.0f , 0.0f   ,0.0f, 0.0f, 1.0f, 0.0f, 1.0f,	1.0f , 0.0f ,
		400.0f , 400.0f ,0.0f, 0.0f, 0.0f, 1.0f, 1.0f,	1.0f , 1.0f ,
		0.0f   , 400.0f ,0.0f, 1.0f, 1.0f, 0.0f, 1.0f,	0.0f , 1.0f ,
	};
	unsigned int indices2[] = {
		0 , 1, 2,
		2 ,3 ,0
	};
	IndexBuffer ib(indices2, 6);
	ib.Bind();
	VertexBuffer vbo(verticies, sizeof(verticies));
	VertexArray vao;
	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(4);
	layout.Push<float>(2);


	vao.AddBuffer(vbo, layout);


	Shader shader("res/shaders/texture_color.shader");
	shader.Bind();
	shader.SetUniform1i("u_Texture1", 0);
	shader.SetUniform1i("u_Texture2", 1);
	Texture texture1("res/textures/container.jpg"), texture2("res/textures/awesomeface.png");
	texture1.Bind(0);
	texture2.Bind(1);
	glm::mat4 m_Proj, m_View, m_Model, m_MVP;
	glm::vec3 m_Translation;
	m_Proj = (glm::ortho(0.0f, 800.0f, 0.0f, 800.0f, -100.0f, 100.0f));
	m_View = (glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)));
	m_Translation = (glm::vec3(0, 0, 0));
	m_Model = glm::translate(glm::mat4(1.0f), m_Translation);
	m_MVP = m_Proj * m_View * m_Model;
	shader.setUniformMat4f("u_MVP", m_MVP);
	
	
	
	
	//-----------------------------------------------------------------------------------------------------
	
	
	
	
	
	test::Test* currentTest = nullptr;
	test::TestMenu* testsMenu = new test::TestMenu(currentTest);
	currentTest = testsMenu;
	testsMenu->AddTest<test::TestClearColor>("Clear Color");
	testsMenu->AddTest<test::TestTexture2D>("2D Texture");
	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	myImGuiManager myImGui(window, width, height);
	while (!glfwWindowShouldClose(window)) {
		renderer.Clear();
		GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		//GLCall(glDisable(GL_DEPTH_TEST));
	
		renderer.Draw(vao, ib, shader);
		glfwPollEvents();


		myImGui.BeginFrame();
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