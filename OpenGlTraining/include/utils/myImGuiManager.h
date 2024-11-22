#pragma once
#include <imGui/imgui_impl_glfw.h>
#include <glm/glm.hpp>
class myImGuiManager {
private:
    int m_Width, m_Height;
public:
    myImGuiManager(GLFWwindow*& window, int& width, int& height);
    ~myImGuiManager();
   

    void BeginFrame();

    void EndFrame();

    void debugV3Slider(glm::vec3& vector, const char* name, float from, float to);
    void debugV3Input(glm::vec3& vector, const char* name, float from, float to);

};

