#include "TestTexture2D.h"
#include "GLErrorManager.h"
#include "imGui/imgui.h"
#include <Renderer.h>
#include <Math.h>
#include <GLFW/glfw3.h>

test::TestTexture2D::TestTexture2D() :
	m_Proj(glm::perspective(glm::radians(45.0f), (float)Application::m_Width / Application::m_Height, 0.1f, 2000.0f)),
	//m_Proj(glm::ortho(0.0f, 800.0f, 0.0f, 800.0f, -100.0f, 100.0f)),
	m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -400.0f))),
	m_Translation(glm::vec3(0, 0, 0)),
	m_Translation2(glm::vec3(0, 0, 0))
{
	//float verticies[] = {
	//	 //Center the object around (400, 400)
	//	 400.0f,	400.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // Bottom-left
	//	 800.0f, 400.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, // Bottom-right
	//	 800.0f,  800.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, // Top-right
	//	400.0f,  800.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f  // Top-left
	//};

	
	float vertices[] = { -0.5f,-0.5f,-0.5f, 0.0f, 0.0f,
 0.5f,-0.5f,-0.5f, 1.0f, 0.0f,
 0.5f, 0.5f,-0.5f, 1.0f, 1.0f,
 0.5f, 0.5f,-0.5f, 1.0f, 1.0f,
		-0.5f, 0.5f,-0.5f, 0.0f,1.0f,-0.5f,-0.5f,-0.5f, 0.0f,0.0f,-0.5f,-0.5f, 0.5f, 0.0f,0.0f,
 0.5f,-0.5f, 0.5f, 1.0f,0.0f,
 0.5f, 0.5f, 0.5f, 1.0f,1.0f,
 0.5f, 0.5f, 0.5f, 1.0f,1.0f,-0.5f, 0.5f, 0.5f, 0.0f,1.0f,-0.5f,-0.5f, 0.5f, 0.0f,0.0f,-0.5f, 0.5f, 0.5f, 1.0f,0.0f,-0.5f, 0.5f,-0.5f, 1.0f,1.0f,-0.5f,-0.5f,-0.5f, 0.0f,1.0f,-0.5f,-0.5f,-0.5f, 0.0f,1.0f,-0.5f,-0.5f, 0.5f, 0.0f,0.0f,-0.5f, 0.5f, 0.5f, 1.0f,0.0f,
 0.5f, 0.5f, 0.5f, 1.0f,0.0f,
 0.5f, 0.5f,-0.5f, 1.0f,1.0f,
 0.5f,-0.5f,-0.5f, 0.0f,1.0f,
 0.5f,-0.5f,-0.5f, 0.0f,1.0f,
 0.5f,-0.5f, 0.5f, 0.0f,0.0f,
 0.5f, 0.5f, 0.5f, 1.0f,0.0f,-0.5f,-0.5f,-0.5f, 0.0f,1.0f,
 0.5f,-0.5f,-0.5f, 1.0f,1.0f,
 0.5f,-0.5f, 0.5f, 1.0f,0.0f,
 0.5f,-0.5f, 0.5f, 1.0f,0.0f,-0.5f,-0.5f, 0.5f, 0.0f,0.0f,-0.5f,-0.5f,-0.5f, 0.0f,1.0f,-0.5f, 0.5f,-0.5f, 0.0f,1.0f,
 0.5f, 0.5f,-0.5f, 1.0f,1.0f,
 0.5f, 0.5f, 0.5f, 1.0f,0.0f,
 0.5f, 0.5f, 0.5f, 1.0f,0.0f,-0.5f, 0.5f, 0.5f, 0.0f,0.0f,-0.5f, 0.5f,-0.5f, 0.0f,1.0f
	};
	//float verticies[] = {
	//	// position			   color						textures
	//	-100.0f   , -50.0f   ,1.0f, 1.0f, 0.0f, 0.0f, 1.0f,	0.0f , 0.0f ,
	//	100.0f , -50.0f   ,1.0f, 0.0f, 1.0f, 0.0f, 1.0f,	1.0f , 0.0f ,
	//	100.0f , 50.0f ,1.0f, 0.0f, 0.0f, 1.0f, 1.0f,	1.0f , 1.0f ,
	//	-100.0f   , 50.0f ,1.0f, 1.0f, 1.0f, 0.0f, 1.0f,	0.0f , 1.0f ,
	//};
	unsigned int indices2[] = {
		0 , 1, 2,
		2 ,3 ,0
	};


	//m_VBO = std::make_unique<VertexBuffer>(verticies, sizeof(verticies));
	m_VBO = std::make_unique<VertexBuffer>(vertices, sizeof(vertices));
	VertexBufferLayout layout;
	layout.Push<float>(3);
	//layout.Push<float>(4);
	layout.Push<float>(2);
	m_EBO = std::make_unique<IndexBuffer>(indices2, 6);

	m_VAO = std::make_unique<VertexArray>();
	m_VAO->AddBuffer(*m_VBO, layout);

	m_Texture = std::make_unique<Texture>("res/textures/container.jpg");
	m_Texture->Bind(3);
	m_Shader = std::make_unique<Shader>("res/shaders/texture.shader");
	//m_Shader = std::make_unique<Shader>("res/shaders/texture.shader");

	m_Shader->Bind();
	m_Shader->SetUniform1i("u_Texture", 3); // 0 is slot number. it should match with slot we chose
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

	GLCall(glClearColor(1.0f, 1.0f, 1.0f, 1.f));
	GLCall(glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT));
	m_Shader->Bind();
	m_Model = glm::mat4(1.0f);
	m_Model = glm::translate(m_Model, m_Translation2);
	m_Model = glm::rotate(m_Model, glm::radians(m_Rotation2), glm::vec3(0.0f, 1.0f, 0.0f));
	m_Model = glm::translate(m_Model, m_Translation);
	m_Model = glm::rotate(m_Model, glm::radians(m_Rotation), glm::vec3(0.0f, 0.0f, 1.0f));
	m_Model = glm::scale(m_Model, glm::vec3(m_Scale, m_Scale, m_Scale));
	m_Model = glm::rotate(m_Model, glm::radians((float)glfwGetTime() * 0.1f), glm::vec3(0.0f, 1.0f, 0.0f));
	m_MVP = m_Proj * m_View * m_Model;

	m_Shader->setUniformMat4f("u_MVP", m_MVP);

	Renderer renderer;
	//renderer.Draw(*m_VAO, *m_EBO, *m_Shader);
	GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
	glm::vec3 cubePositions[] = {
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

	for (unsigned int i = 1; i < 10; i++)
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(m_Scale, m_Scale, m_Scale)* cubePositions[i]);
		float angle = 20.0f * i;
		if (i % 3 == 0)  // every 3rd iteration (including the first) we set the angle using GLFW's time function.
			angle = glfwGetTime() * 25.0f;
		model = glm::rotate(model, glm::radians(angle),
			glm::vec3(1.0f, 0.3f, 0.5f));
		model = glm::scale(model, glm::vec3(m_Scale, m_Scale, m_Scale));
		m_MVP = m_Proj * m_View * model;
		m_Shader->setUniformMat4f("u_MVP", m_MVP);
		GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
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

	ImGui::SliderFloat("Scale", (float*)&m_Scale, -10.0f, 1000.0f);
}
