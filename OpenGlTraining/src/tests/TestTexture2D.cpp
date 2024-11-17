#include "TestTexture2D.h"
#include "GLErrorManager.h"
#include "imGui/imgui.h"
#include <Renderer.h>

test::TestTexture2D::TestTexture2D() :
	//m_Proj(glm::perspective(glm::radians(45.0f), 800.0f / 800.0f, -800.0f, 800.0f)),
	m_Proj(glm::ortho(0.0f, 800.0f, 0.0f, 800.0f, -100.0f, 100.0f)),
	m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))),
	m_Translation(glm::vec3(0, 0, 0))
{
	float verticies[] = {
		// position			   color						textures
		0.0f   , 0.0f   ,1.0f, 1.0f, 0.0f, 0.0f, 1.0f,	0.0f , 0.0f ,
		800.0f , 0.0f   ,1.0f, 0.0f, 1.0f, 0.0f, 1.0f,	1.0f , 0.0f ,
		800.0f , 800.0f ,1.0f, 0.0f, 0.0f, 1.0f, 1.0f,	1.0f , 1.0f ,
		0.0f   , 800.0f ,1.0f, 1.0f, 1.0f, 0.0f, 1.0f,	0.0f , 1.0f ,
	};
	unsigned int indices2[] = {
		0 , 1, 2,
		2 ,3 ,0
	};


	m_VBO = std::make_unique<VertexBuffer>(verticies, sizeof(verticies));

	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(4);
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
	m_MVP = m_Proj * m_View * m_Model;

	GLCall(glEnable(GL_DEPTH_TEST));
	//GLCall(glEnable(GL_BLEND));
	//GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

}


test::TestTexture2D::~TestTexture2D()
{
}

void test::TestTexture2D::OnUpdate(float deltaTime)
{
}

void test::TestTexture2D::OnRender()
{
	GLCall(glClearColor(1.0f, 1.0f, 1.0f, 1.f));
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
	m_Shader->Bind();
	
	m_Model = glm::translate(glm::mat4(1.0f), m_Translation);
	m_MVP = m_Proj * m_View * m_Model;
	m_Shader->setUniformMat4f("u_MVP", m_MVP);

	Renderer renderer;
	renderer.Draw(*m_VAO, *m_EBO, *m_Shader);
}

void test::TestTexture2D::OnImGuiRender()
{

	ImGui::SliderFloat3("Translation", (float*)&m_Translation.x, 0.0f, 800.0f);
}
