#include "Scene.h"
#include "Application.h"
Scene::Scene() :
	m_Proj(glm::perspective(glm::radians(45.0f), (float)Window::getWidth() / Window::getHeight(), 0.1f, 2000.0f)),
	//m_Proj(glm::ortho(0.0f, 800.0f, 0.0f, 800.0f, -100.0f, 100.0f)),
	m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0.0f))),
	m_Cube(100.0f)
{
}

Scene::~Scene()
{
}

void Scene::onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode, float deltaTime)
{
	//if (action == GLFW_REPEAT) {
	//	return;  // don't respond to repeatedly pressed buttons
	//}

	bool isButtonPressed = action == GLFW_PRESS;

	if (key == GLFW_KEY_W || key == GLFW_KEY_UP) {
		camera.ProcessKeyboard(FORWARD, deltaTime);
	}
	else if (key == GLFW_KEY_S || key == GLFW_KEY_DOWN) {
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	}
	else if (key == GLFW_KEY_A || key == GLFW_KEY_LEFT) {
		camera.ProcessKeyboard(LEFT, deltaTime);
	}
	else if (key == GLFW_KEY_D || key == GLFW_KEY_RIGHT) {
		camera.ProcessKeyboard(RIGHT, deltaTime);
	}
	else if (key == GLFW_KEY_SPACE) {

		//camera.setIsMovingUp(isButtonPressed);

	}
	else if (key == GLFW_KEY_LEFT_CONTROL || key == GLFW_KEY_RIGHT_CONTROL) {
		//camera.setIsMovingDown(isButtonPressed);
	}
}

void Scene::render()
{
	m_Cube.SetView(camera.GetViewMatrix());
	glm::vec3 axis(1.0f, 1.0f, 0.0f);
	m_Cube.Rotate(m_Rotation, axis);
	m_Cube.draw();
}
