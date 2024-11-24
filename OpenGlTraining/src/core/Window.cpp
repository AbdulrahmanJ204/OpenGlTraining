#include "Window.h"
#include "Application.h"
Window* Window::instancePtr = nullptr;
int Window::s_Width = 1800;
int Window::s_Height= 900;


Window::Window(std::string title, int width , int height) :
	m_Title(title), m_Window(nullptr), m_Monitor(nullptr)
{
	s_Width = (width), s_Height = (height);
	if(!initGLFW() ) return;
	if(initGLAD()) return;
	instancePtr = this;
	setupCallbacks();
}

Window::~Window()
{	
	instancePtr = nullptr;
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
	
	m_Window = glfwCreateWindow(s_Width, s_Height, m_Title.c_str(), NULL, NULL);
	if (m_Window == NULL) {
		spdlog::error("Failed to create GLFW window");
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(m_Window);
	// v-sync
	glfwSwapInterval(1);
	instancePtr = this;
	m_initalized = true;
	setupCallbacks();
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

void Window::onWindowError(int32_t errorCode, const char* description) {
	std::cerr << "GLFW: **ERROR** error=" << errorCode << " description=" << description << std::endl;
}

void Window::onKeyEvent(GLFWwindow*, int32_t key, int32_t scancode, int32_t action, int32_t mode) {
	
	Application::instance().onKeyEvent(key, scancode, action, mode);
}

void Window::onResized(GLFWwindow*, int32_t width, int32_t height) {
	
	Application& app = Application::instance();
	Window& window = app.getWindow();
	//window.setWindowHeight(height);
	//window.setWindowWidth(width);

	//app.onResized(width, height);
}

void Window::onMouseButtonEvent(GLFWwindow*, int32_t button, int32_t action, int32_t mods) {
	
	//Application::instance().onMouseButtonEvent(button, action, mods);
}

void Window::onCursorPosition(GLFWwindow*, double x, double y) {
	
	Application::instance().onCursorPositionEvent(x, y);
}

void Window::onRefreshWindow(GLFWwindow*) {
	
	//Application::instance().onRefreshWindow();
}


void Window::setupCallbacks() {
	
	glfwSetKeyCallback(m_Window, onKeyEvent);
	//glfwSetMouseButtonCallback(m_Window, onMouseButtonEvent);
	//glfwSetCursorPosCallback(m_Window, onCursorPosition);
	glfwSetFramebufferSizeCallback(m_Window, onResized);
//
//#ifndef BUILD_TYPE_DIST
//	glEnable(GL_DEBUG_OUTPUT);
//	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
//	glDebugMessageCallback(onOpenGlMessage, nullptr);
//	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
//#endif
	glfwSwapInterval(1);

	glfwSetWindowRefreshCallback(m_Window, onRefreshWindow);
	glfwSetErrorCallback(Window::onWindowError);
}
