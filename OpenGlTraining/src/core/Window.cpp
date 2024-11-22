#include "Window.h"

GLFWwindow* Window::ptr = nullptr;
int Window::s_Width = 800;          // Initialize with default width
int Window::s_Height = 600;         // Initialize with default height
bool Window::updateViewPort = true; // Default: viewport needs updating
bool Window::s_IsFullScreen = false;
bool Window::s_initalized = false;

Window::Window(std::string title, int width , int height) :
	m_Title(title), m_Window(nullptr), m_Monitor(nullptr)
{
	s_Width = width;
	s_Height = height;
	bool x = false;
	initGLFW();
	initGLAD();

}

Window::~Window()
{
	if (m_Window) {
		glfwDestroyWindow(m_Window);
	}
	glfwTerminate();
}

bool Window::initGLFW()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	if(s_IsFullScreen)
		m_Monitor = glfwGetPrimaryMonitor();;
	m_Window = glfwCreateWindow(s_Width, s_Height, m_Title.c_str(), NULL, NULL);
	if (m_Window == NULL) {
		spdlog::error("Failed to create GLFW window");
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(m_Window);
	// v-sync
	Window::SetVSync(1);
	ptr = m_Window;
	s_initalized = true;
	return true;
}

bool Window::initGLAD()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		spdlog::error("Failed to initialize GLAD");
		return false;
	}
	return true;
}
