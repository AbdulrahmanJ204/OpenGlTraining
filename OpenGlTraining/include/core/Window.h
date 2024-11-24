#pragma once // instead of ifndef

#include "core.h"

class Window {
public:

	Window(std::string title, int width , int height);
	~Window();

	
	inline void swapBuffers() { glfwSwapBuffers(m_Window);}
	
	inline GLFWwindow* getWindow () const { return m_Window; };
	inline Window& instance() { return *instancePtr; }
	static inline int getWidth() { return s_Width; }
	static inline int getHeight(){ return s_Height; }
	inline bool shouldClose() { return glfwWindowShouldClose(m_Window);}
	void setupCallbacks();

	
	static void onKeyEvent(GLFWwindow* window, int32_t key, int32_t scancode, int32_t action, int32_t mode);
	static void onResized(GLFWwindow* window, int32_t width, int32_t height);
	static void onMouseButtonEvent(GLFWwindow* window, int32_t button, int32_t action, int32_t mods);
	static void onCursorPosition(GLFWwindow* window, double x, double y);
	static void onRefreshWindow(GLFWwindow* window);
	static void onWindowError(int32_t errorCode, const char* description);
	//static void onOpenGlMessage(GLenum source,
	//	GLenum type,
	//	GLuint id,
	//	GLenum severity,
	//	GLsizei length,
	//	const GLchar* message,
	//	const void* userParam);


private:
	static Window* instancePtr;
	static int s_Width, s_Height ;
	bool m_initalized = false;
	GLFWwindow* m_Window;
	GLFWmonitor* m_Monitor;
	std::string m_Title;
	int m_Pos[2] = { 0,0 };
	
	bool initGLFW();
	bool initGLAD();
};