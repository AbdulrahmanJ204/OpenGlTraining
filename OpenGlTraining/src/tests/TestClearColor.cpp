#include "TestClearColor.h"
#include "GLErrorManager.h"
#include "imGui/imgui.h"
test::TestClearColor::TestClearColor():
	m_ClearColor{1.0f , 0.5f , 0.8f , 1.0f}
{

}

test::TestClearColor::~TestClearColor()
{
}

void test::TestClearColor::OnUpdate(float deltaTime)
{
}

void test::TestClearColor::OnRender()
{
	GLCall(glClearColor(m_ClearColor[0],m_ClearColor[1],m_ClearColor[2],m_ClearColor[3]))
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void test::TestClearColor::OnImGuiRender()
{
	ImGui::ColorEdit4("Color Change", m_ClearColor);
}
