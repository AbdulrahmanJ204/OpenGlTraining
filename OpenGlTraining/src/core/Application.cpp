#include"Application.h"
Application* Application::instancePtr = nullptr;
Application::Application()
	:
	lastX(0.0f) , lastY(0.0f),
	window("Test", 1800, 900)
{
	spdlog::info("Starting Application");	
	instancePtr = this;
	
}

Application::~Application()
{

	instancePtr = nullptr;
}
void Application::LoadImGui(myImGuiManager& myImGui)
{
	/*myImGui.BeginFrame();
	myImGui.EndFrame();*/
}

void Application::run() {
	

	GLCall(glEnable(GL_DEPTH_TEST));
	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	lastX = window.getWidth() / 2.0f;
	lastY = window.getHeight() / 2.0f;
	
	glm::vec3 axis = glm::vec3(1.0f, 1.0f, 1.0f);
		float angle =  35.0f;
		
	while (! window.shouldClose()) {
		GLCall(glClearColor(0.3f, 0.5f, 0.8f, 1.0f));
		m_Renderer.Clear();

		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		//float angle = (float)glfwGetTime() * 50.0f;
		scene.render();
		
		
		glfwPollEvents();
		//LoadImGui(myImGui);
		window.swapBuffers();
	}

}
void Application::processInput()
{
}
float Application::getRandom()
{
	return (float)(rand() % 100) / 100;
}




void Application::onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) {
	scene.onKeyEvent(key , scancode, action  , mode, deltaTime);
}


void Application::onCursorPositionEvent(double x, double y) {
	static double lastX = x;
	static double lastY = y;

	/*if (shouldResetMouse) {
		shouldResetMouse = false;
		lastX = x;
		lastY = y;
	}*/

	/*float yaw = camera.getYaw() + static_cast<float>(-lastX + x) * mouseSensitivity;
	float pitch = glm::clamp(camera.getPitch() + static_cast<float>(lastY - y) * mouseSensitivity, -89.0f, 89.0f);
	camera.updateCameraOrientation(yaw, pitch);*/

	lastX = x;
	lastY = y;
}