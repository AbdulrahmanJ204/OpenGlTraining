#include "Cube.h"
#include <Application.h>

Cube::Cube(float sideLength) :
	m_Length(sideLength),
	m_MVP(glm::mat4(1.0f)),
	m_Proj(glm::perspective(glm::radians(45.0f), (float)Application::m_Width / Application::m_Height, 0.1f, 2000.0f)),
	m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -400.0f)))
{
	float vertices[] = {
 
 -0.5f * sideLength,-0.5f * sideLength,-0.5f * sideLength, 0.0f,0.0f,
  0.5f * sideLength,-0.5f * sideLength,-0.5f * sideLength, 1.0f,0.0f,
  0.5f * sideLength, 0.5f * sideLength,-0.5f * sideLength, 1.0f,1.0f,
  0.5f * sideLength, 0.5f * sideLength,-0.5f * sideLength, 1.0f,1.0f,

 -0.5f * sideLength, 0.5f * sideLength,-0.5f * sideLength, 0.0f,1.0f,
 -0.5f * sideLength,-0.5f * sideLength,-0.5f * sideLength, 0.0f,0.0f,
 -0.5f * sideLength,-0.5f * sideLength, 0.5f * sideLength, 0.0f,0.0f,
  0.5f * sideLength,-0.5f * sideLength, 0.5f * sideLength, 1.0f,0.0f,

 
  0.5f * sideLength, 0.5f * sideLength, 0.5f * sideLength, 1.0f,1.0f,
  0.5f * sideLength, 0.5f * sideLength, 0.5f * sideLength, 1.0f,1.0f,
 -0.5f * sideLength, 0.5f * sideLength, 0.5f * sideLength, 0.0f,1.0f,
 -0.5f * sideLength,-0.5f * sideLength, 0.5f * sideLength, 0.0f,0.0f,
 
 -0.5f * sideLength, 0.5f * sideLength, 0.5f * sideLength, 1.0f,0.0f,
 -0.5f * sideLength, 0.5f * sideLength,-0.5f * sideLength, 1.0f,1.0f,
 -0.5f * sideLength,-0.5f * sideLength,-0.5f * sideLength, 0.0f,1.0f,
 -0.5f * sideLength,-0.5f * sideLength,-0.5f * sideLength, 0.0f,1.0f,
 
 -0.5f * sideLength,-0.5f * sideLength, 0.5f * sideLength, 0.0f,0.0f,
 -0.5f * sideLength, 0.5f * sideLength, 0.5f * sideLength, 1.0f,0.0f,
  0.5f * sideLength, 0.5f * sideLength, 0.5f * sideLength, 1.0f,0.0f,
  0.5f * sideLength, 0.5f * sideLength,-0.5f * sideLength, 1.0f,1.0f,
  
 
  0.5f * sideLength,-0.5f * sideLength,-0.5f * sideLength, 0.0f,1.0f,
  0.5f * sideLength,-0.5f * sideLength,-0.5f * sideLength, 0.0f,1.0f,
  0.5f * sideLength,-0.5f * sideLength, 0.5f * sideLength, 0.0f,0.0f,
  0.5f * sideLength, 0.5f * sideLength, 0.5f * sideLength, 1.0f,0.0f,
 
 -0.5f * sideLength,-0.5f * sideLength,-0.5f * sideLength, 0.0f,1.0f,
  0.5f * sideLength,-0.5f * sideLength,-0.5f * sideLength, 1.0f,1.0f,
  0.5f * sideLength,-0.5f * sideLength, 0.5f * sideLength, 1.0f,0.0f,
  0.5f * sideLength,-0.5f * sideLength, 0.5f * sideLength, 1.0f,0.0f,
 
 -0.5f * sideLength,-0.5f * sideLength, 0.5f * sideLength, 0.0f,0.0f,
 -0.5f * sideLength,-0.5f * sideLength,-0.5f * sideLength, 0.0f,1.0f,
 -0.5f * sideLength, 0.5f * sideLength,-0.5f * sideLength, 0.0f,1.0f,
  0.5f * sideLength, 0.5f * sideLength,-0.5f * sideLength, 1.0f,1.0f,
 

  0.5f * sideLength, 0.5f * sideLength, 0.5f * sideLength, 1.0f,0.0f,
  0.5f * sideLength, 0.5f * sideLength, 0.5f * sideLength, 1.0f,0.0f,
 -0.5f * sideLength, 0.5f * sideLength, 0.5f * sideLength, 0.0f,0.0f,
 -0.5f * sideLength, 0.5f * sideLength,-0.5f * sideLength, 0.0f,1.0f
};
	m_VBO = std::make_unique<VertexBuffer>(vertices, sizeof(vertices));
	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(2);
	m_VAO = std::make_unique<VertexArray>();
	m_VAO->AddBuffer(*m_VBO, layout);
	m_Texture = std::make_unique<Texture>("res/textures/container.jpg");
	m_Shader = std::make_unique<Shader>("res/shaders/texture.shader");
	m_Texture->Bind();
	m_Shader->Bind();
	m_Shader->SetUniform1i("u_Texture", 0); // 0 is slot number. it should match with slot we chose
	m_Shader->setUniformMat4f("u_MVP", glm::mat4(1.0f));

}

Cube::~Cube()
{
}

void Cube::draw()
{
	m_Texture->Bind();
	m_Shader->Bind();
	m_Shader->SetUniform1i("u_Texture", 0); // 0 is slot number. it should match with slot we chose

	m_Model = glm::rotate(glm::mat4(1.0f), glm::radians((float)glfwGetTime()* 25.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	m_MVP = m_Proj * m_View * m_Model;
	m_Shader->setUniformMat4f("u_MVP", m_MVP);

	GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
}
