#include "TestTexture2D.h"
#include "GLErrorManager.h"
#include "imGui/imgui.h"
#include <Renderer.h>
#include <Math.h>
#include <GLFW/glfw3.h>
#include <Cube.h>

test::TestTexture2D::TestTexture2D() :
	m_Proj(glm::perspective(glm::radians(45.0f), (float)Application::m_Width / Application::m_Height, 0.1f, 2000.0f)),
	//m_Proj(glm::ortho(0.0f, 800.0f, 0.0f, 800.0f, -100.0f, 100.0f)),
	m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -400.0f))),
	m_Translation(glm::vec3(0, 0, 0)),
	m_Translation2(glm::vec3(0, 0, 0)),
	m_Cube(100.0f)
{

	m_Model = glm::translate(glm::mat4(1.0f), m_Translation);
	m_Model = glm::rotate(m_Model, glm::radians(m_Rotation), glm::vec3(0.0f, 0.0f, 1.0f));
	m_MVP = m_Proj * m_View * m_Model;

	GLCall(glEnable(GL_DEPTH_TEST));
	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

}


test::TestTexture2D::~TestTexture2D()
{
}

void test::TestTexture2D::OnUpdate(float deltaTime)
{
	if (m_Rotation > 360.0f) m_Rotation = m_RotaionIncreamnt;
	if (m_Rotation2 > 360.0f) m_Rotation2 = m_RotaionIncreamnt2;
	//m_Rotation += m_RotaionIncreamnt;
	/*m_Rotation2 += m_RotaionIncreamnt2;
	m_Rotation = - m_Rotation2;
	static float x = 0.5f, inc = 0.01f;
	if (x > acos(-1) || x<0.0f) inc *= -1.0f;
	x += inc;*/
	//m_Scale = static_cast<float>(sin(glfwGetTime()));
}

void test::TestTexture2D::OnRender()
{
	GLCall(glClearColor(1.0f, 1.0f, 1.0f, 1.0f));
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	glm::vec3 axis = glm::vec3(1.0f, 1.0f, 0.0f);
	glm::vec3 pviot = glm::vec3(0.0f, 0.0f, 0.0f);
	//m_Rotation = (float)glfwGetTime() * 25.0f;
	m_Rotation = 1.0f;
	const float radius = 10.0f;
	float camX = sin(glfwGetTime()) * radius;
	float camZ = cos(glfwGetTime()) * radius;
	glm::mat4 view;
	view = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0),
		glm::vec3(0.0, 1.0, 0.0));
	m_Cube.SetView(view);
	glm::vec3 cubePositions[] = {
	 glm::vec3(1.0f, 2.0f, 5.0f),
	 glm::vec3(2.0f, 5.0f,-15.0f),
	 glm::vec3(-1.5f,-2.2f,-2.5f),
	 glm::vec3(-3.8f,-2.0f,-12.3f),
	 glm::vec3(2.4f,-0.4f,-3.5f),
	 glm::vec3(-1.7f, 3.0f,-7.5f),
	 glm::vec3(1.3f,-2.0f,2.5f),
	 glm::vec3(1.5f, 2.0f,-2.5f),
	 glm::vec3(1.5f, 0.2f,1.5f),
	 glm::vec3(-1.3f, 1.0f,-1.5f)
	};
	//m_Cube.RotateAroundAxis(m_Rotation, axis, pviot);
	//m_Cube.Rotate(m_Rotation, axis);
	glm::vec3 sc = glm::vec3(m_Scale, m_Scale, m_Scale);
	for (size_t i = 0; i < 10; i++)
	{
		glm::vec3 pos = glm::vec3(100.0f, 100.0f, 100.0f) * cubePositions[i];
		m_Cube.Translate(pos);
		m_Cube.Scale(sc);
		m_Cube.draw();
	}
}

void test::TestTexture2D::OnImGuiRender()
{
	ImGui::SliderFloat3("Translation", (float*)&m_Translation.x, -800.0f, 800.0f);
	ImGui::SliderFloat3("Translation 2", (float*)&m_Translation2.x, -800.0f, 800.0f);
	ImGui::SliderFloat("Rotation", (float*)&m_Rotation, 0.0f, 360.0f);
	ImGui::SliderFloat("Rotation 2", (float*)&m_Rotation2, 0.0f, 360.0f);
	ImGui::SliderFloat("Rotation Increament", (float*)&m_RotaionIncreamnt, 0.0f, 360.0f);
	ImGui::SliderFloat("Rotation Increament2", (float*)&m_RotaionIncreamnt2, 0.0f, 360.0f);
	ImGui::SliderFloat("Scale", (float*)&m_Scale, -3.0f, 3.0f);
}
