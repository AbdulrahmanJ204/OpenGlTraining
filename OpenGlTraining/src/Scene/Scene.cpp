#include "Scene.h"
#include "Application.h"
Scene* Scene::instancePtr = nullptr;

Scene::Scene() :
	lastX(0.0f), lastY(0.0f),firstMouse(true),
	//m_Proj(glm::mat4(1.0f)),
	m_Proj(glm::perspective(glm::radians(45.0f), (float)Window::getWidth() / Window::getHeight(), 0.1f, 100.0f)),
	//m_Proj(glm::ortho(0.0f, 800.0f, 0.0f, 800.0f, -100.0f, 100.0f)),
	m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 20.0f))),
	camera(glm::vec3(0, 0, 20.0f)),
	modelShader("assets/shaders/model_loading.vert", "assets/shaders/model_loading.frag"),
	m_Model("assets/objects/backpack/backpack.obj")
{

	instancePtr = this;
	
	lastX = Window::getWidth() / 2.0f;
	lastY = Window::getHeight() / 2.0f;
	modelShader.Bind();
	modelShader.setUniformMat4f("projection", m_Proj);
	modelShader.setUniformMat4f("view", m_View);
	
	/*m_Cube = Cube(100.0f);
	m_Cube.SetProj(m_Proj);
	m_Cube.SetView(m_View);*/
}
void Scene::render()
{
	 
	glm::mat4 view = camera.GetViewMatrix();
	modelShader.setUniformMat4f("view", view);

	// render the loaded model
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
	model = glm::scale(model, glm::vec3(m_Rotation , m_Rotation , m_Rotation));	// it's a bit too big for our scene, so scale it down
	modelShader.setUniformMat4f("model", model);
	m_Model.Draw(modelShader);
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
		int mode  = glfwGetInputMode(Window::instancePtr->getWindow(),GLFW_CURSOR);
		glfwSetInputMode(Window::instancePtr->getWindow(), GLFW_CURSOR, mode == GLFW_CURSOR_DISABLED ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);

	}

}

void Scene::onCursorPositionEvent(double x, double y)
{
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

