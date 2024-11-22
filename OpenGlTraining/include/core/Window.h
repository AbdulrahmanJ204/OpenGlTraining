#pragma once // instead of ifndef

#include "core.h"

class Window {
public:

	Window(std::string title, int width , int height);
	~Window();

	
	inline void Update() { glfwSwapBuffers(ptr);}
	
	static inline GLFWwindow& getWindow() { return *ptr; }
	static inline int GetWidth() { return s_Width; }
	static inline int GetHeight() { return s_Height; }
	static inline void SetVSync(int on = 1){
		glfwSwapInterval(1);
	}
	static inline bool ShouldClose() { return glfwWindowShouldClose(ptr);}
	//static void onKeyEvent(GLFWwindow* window, int32_t key, int32_t scancode, int32_t action, int32_t mode);
	//static void onResized(GLFWwindow* window, int32_t width, int32_t height);
	//static void onMouseButtonEvent(GLFWwindow* window, int32_t button, int32_t action, int32_t mods);
	//static void onCursorPosition(GLFWwindow* window, double x, double y);
	//static void onRefreshWindow(GLFWwindow* window);

	/*static void onWindowError(int32_t errorCode, const char* description);
	static void onOpenGlMessage(GLenum source,
		GLenum type,
		GLuint id,
		GLenum severity,
		GLsizei length,
		const GLchar* message,
		const void* userParam);*/

private:
	static GLFWwindow* ptr;
	static int s_Width, s_Height;
	static bool updateViewPort;
	static bool s_IsFullScreen;
	static bool s_initalized;
	GLFWwindow* m_Window;
	GLFWmonitor* m_Monitor;
	std::string m_Title;
	int m_Pos[2] = { 0,0 };
	
	
	bool initGLFW();
	bool initGLAD();
	//int m_Size[2] = { 0,0 }; 

};