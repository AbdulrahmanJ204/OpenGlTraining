#include "Scene.h"
#include "Application.h"
Scene* Scene::instancePtr = nullptr;

Scene::Scene() :
	lastX(0.0f), lastY(0.0f), firstMouse(true),
	//m_Proj(glm::mat4(1.0f)),
	m_Proj(glm::perspective(glm::radians(45.0f), (float)Window::getWidth() / Window::getHeight(), 0.1f, 1000.0f)),
	//m_Proj(glm::ortho(0.0f, 800.0f, 0.0f, 800.0f, -100.0f, 100.0f)),
	m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 20.0f))),
	m_LightPos(30.0f, 30.0f, 30.0f),
	camera(glm::vec3(0, 0, 20.0f))
{

	instancePtr = this;

	lastX = Window::getWidth() / 2.0f;
	lastY = Window::getHeight() / 2.0f;
	m_LightCube = Cube(3.0f, "assets/shaders/light_cube.vert", "assets/shaders/light_cube.frag", m_LightPos);
	m_LightCube.SetProj(m_Proj);
	m_LightCube.SetView(m_View);


	glm::vec3 init[] = {
	 glm::vec3(0.0f, 0.0f, 0.0f),
	 glm::vec3(2.0f, 5.0f,-15.0f),
	 glm::vec3(-1.5f,-2.2f,-2.5f),
	 glm::vec3(-3.8f,-2.0f,-12.3f),
	 glm::vec3(2.4f,-0.4f,-3.5f),
	 glm::vec3(-1.7f, 3.0f,-7.5f),
	 glm::vec3(1.3f,-2.0f,-2.5f),
	 glm::vec3(1.5f, 2.0f,-2.5f),
	 glm::vec3(1.5f, 0.2f,-1.5f),
	 glm::vec3(-1.3f, 1.0f,-1.5f)
	};

	for (int i = 0; i < 10; i++)
	{
		cubePositions[i] = init[i];
		glm::vec3 trans = cubePositions[i] * glm::vec3(10.0f, 10.0f, 10.0f);
		cubes[i] = Cube(10.0f, "assets/shaders/vertex.vert", "assets/shaders/fragment.frag", trans);
		cubes[i].SetProj(m_Proj);
		cubes[i].SetView(m_View);
		cubes[i].SetLightPos(m_LightPos);
	}


}
void Scene::render()
{

	glm::mat4 view = camera.GetViewMatrix();

	for (int i = 0; i < 10; i++)
	{
		cubes[i].SetView(view);
	}
	m_LightCube.SetView(view);

	m_LightCube.Translate(m_LightPos);

	m_LightCube.draw();

	for (int i = 0; i < 10; i++)
	{
		cubes[i].SetLightPos(m_LightCube.getPos());
		cubes[i].draw();
	}
	
}

Scene::~Scene()
{
	instancePtr = nullptr;
}

void Scene::processDiscreteInput(int32_t key, int32_t scancode, int32_t action, int32_t mode, float deltaTime)
{
	static int cnt = 0;
	if (action == GLFW_REPEAT) {
		return;  // don't respond to repeatedly pressed buttons
	}

	if (key == GLFW_KEY_ESCAPE) {
		glfwSetWindowShouldClose(Window::instancePtr->getWindow(), true);
	}
	else if (action == GLFW_PRESS) {
		if (key == GLFW_KEY_F11) {
			Window::instancePtr->toggleFullscreen();
		}
	}
	else if (key == GLFW_KEY_CAPS_LOCK) {
		int mode = glfwGetInputMode(Window::instancePtr->getWindow(), GLFW_CURSOR);
		glfwSetInputMode(Window::instancePtr->getWindow(), GLFW_CURSOR, mode == GLFW_CURSOR_DISABLED ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);

	}

}

void Scene::onCursorPositionEvent(double x, double y)
{
	int mode = glfwGetInputMode(Window::instancePtr->getWindow(), GLFW_CURSOR);
	if (mode == GLFW_CURSOR_NORMAL)
	{
		lastX = Window::getWidth() / 2.0f;
		lastY = Window::getHeight() / 2.0f;
		firstMouse = true;
		return;
	}
	float xpos = static_cast<float>(x);
	float ypos = static_cast<float>(y);

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;
	camera.ProcessMouseMovement(xoffset, yoffset);
}

void Scene::processContinuousInput(float& deltaTime)
{
	GLFWwindow* window = Window::instancePtr->getWindow();
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		getCamera().ProcessKeyboard(FORWARD, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		getCamera().ProcessKeyboard(BACKWARD, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		getCamera().ProcessKeyboard(LEFT, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		getCamera().ProcessKeyboard(RIGHT, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		getCamera().ProcessKeyboard(UP, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
		getCamera().ProcessKeyboard(DOWN, deltaTime);
	}
}

