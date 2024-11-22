#include"Application.h"

Application::Application()
	:window("Test", 1800, 900)
{
	spdlog::info("Starting Application");	
	
}

void Application::LoadImGui(myImGuiManager& myImGui)
{
	/*myImGui.BeginFrame();
	myImGui.EndFrame();*/
}

Application::~Application()
{


}

void Application::run() {
	

	GLCall(glEnable(GL_DEPTH_TEST));
	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	Cube cube(100.0f);
	glm::vec3 axis = glm::vec3(1.0f, 1.0f, 1.0f);
		float angle =  35.0f;
	while (!Window::ShouldClose()) {
		GLCall(glClearColor(0.3f, 0.5f, 0.8f, 1.0f));
		m_Renderer.Clear();
		//float angle = (float)glfwGetTime() * 50.0f;
		cube.Rotate(angle++, axis);
		cube.draw();
		glfwPollEvents();
		//LoadImGui(myImGui);
		window.Update();
	}

}
float Application::getRandom()
{
	return (float)(rand() % 100) / 100;
}




void Application::processInput()

{/*
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		
	}*/
}





