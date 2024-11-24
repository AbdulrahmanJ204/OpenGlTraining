#include "Cube.h"
#include "Scene.h"
Cube::Cube()
{
}

Cube::Cube(float sideLength) :
	m_Length(sideLength),
	m_FScale(1.0f),
	m_Degree(0.0f),
	m_Axis(glm::vec3(1.0f, 1.0f, 1.0f)),
	m_Translate(glm::vec3(1.0f, 1.0f, 1.0f)),
	m_Scale(glm::vec3(1.0f, 1.0f, 1.0f)),
	m_CubeColor(glm::vec3(1.0f, 0.5f, 0.31f)),
	m_LightColor(glm::vec3(1.0f, 1.0f, 1.0f)),
	m_LightPos(glm::vec3(0.0f, 0.0f, 300.0f)),
	m_Model(glm::mat4(1.0f)),
	m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0.0f)))
{
	int width, height;
	glfwGetWindowSize(glfwGetCurrentContext(), &width, &height);
	m_Proj = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 2000.0f);
	float vertices[] = {
 
 -0.5f * sideLength,-0.5f * sideLength,-0.5f * sideLength,  0.0f, 0.0f,-1.0f,  0.0f,0.0f,
  0.5f * sideLength,-0.5f * sideLength,-0.5f * sideLength,  0.0f, 0.0f,-1.0f,  1.0f,0.0f,
  0.5f * sideLength, 0.5f * sideLength,-0.5f * sideLength,  0.0f, 0.0f,-1.0f,  1.0f,1.0f,
  0.5f * sideLength, 0.5f * sideLength,-0.5f * sideLength,  0.0f, 0.0f,-1.0f,  1.0f,1.0f,

 -0.5f * sideLength, 0.5f * sideLength,-0.5f * sideLength,  0.0f, 0.0f,-1.0f,  0.0f,1.0f,
 -0.5f * sideLength,-0.5f * sideLength,-0.5f * sideLength,  0.0f, 0.0f,-1.0f,  0.0f,0.0f,
 -0.5f * sideLength,-0.5f * sideLength, 0.5f * sideLength,  0.0f, 0.0f, 1.0f,  0.0f,0.0f,
  0.5f * sideLength,-0.5f * sideLength, 0.5f * sideLength,  0.0f, 0.0f, 1.0f,  1.0f,0.0f,

 
  0.5f * sideLength, 0.5f * sideLength, 0.5f * sideLength,  0.0f, 0.0f, 1.0f, 1.0f,1.0f,
  0.5f * sideLength, 0.5f * sideLength, 0.5f * sideLength,  0.0f, 0.0f, 1.0f, 1.0f,1.0f,
 -0.5f * sideLength, 0.5f * sideLength, 0.5f * sideLength,  0.0f, 0.0f, 1.0f, 0.0f,1.0f,
 -0.5f * sideLength,-0.5f * sideLength, 0.5f * sideLength,  0.0f, 0.0f, 1.0f, 0.0f,0.0f,
 
 -0.5f * sideLength, 0.5f * sideLength, 0.5f * sideLength, -1.0f, 0.0f, 0.0f, 1.0f,0.0f,
 -0.5f * sideLength, 0.5f * sideLength,-0.5f * sideLength, -1.0f, 0.0f, 0.0f, 1.0f,1.0f,
 -0.5f * sideLength,-0.5f * sideLength,-0.5f * sideLength, -1.0f, 0.0f, 0.0f, 0.0f,1.0f,
 -0.5f * sideLength,-0.5f * sideLength,-0.5f * sideLength, -1.0f, 0.0f, 0.0f, 0.0f,1.0f,
 
 -0.5f * sideLength,-0.5f * sideLength, 0.5f * sideLength, -1.0f, 0.0f, 0.0f, 0.0f,0.0f,
 -0.5f * sideLength, 0.5f * sideLength, 0.5f * sideLength, -1.0f, 0.0f, 0.0f, 1.0f,0.0f,
  0.5f * sideLength, 0.5f * sideLength, 0.5f * sideLength,  1.0f, 0.0f, 0.0f, 1.0f,0.0f,
  0.5f * sideLength, 0.5f * sideLength,-0.5f * sideLength,  1.0f, 0.0f, 0.0f, 1.0f,1.0f,
  
 
  0.5f * sideLength,-0.5f * sideLength,-0.5f * sideLength,  1.0f, 0.0f, 0.0f, 0.0f,1.0f,
  0.5f * sideLength,-0.5f * sideLength,-0.5f * sideLength,  1.0f, 0.0f, 0.0f, 0.0f,1.0f,
  0.5f * sideLength,-0.5f * sideLength, 0.5f * sideLength,  1.0f, 0.0f, 0.0f, 0.0f,0.0f,
  0.5f * sideLength, 0.5f * sideLength, 0.5f * sideLength,  1.0f, 0.0f, 0.0f, 1.0f,0.0f,
 
 -0.5f * sideLength,-0.5f * sideLength,-0.5f * sideLength,  0.0f,-1.0f, 0.0f, 0.0f,1.0f,
  0.5f * sideLength,-0.5f * sideLength,-0.5f * sideLength,  0.0f,-1.0f, 0.0f, 1.0f,1.0f,
  0.5f * sideLength,-0.5f * sideLength, 0.5f * sideLength,  0.0f,-1.0f, 0.0f, 1.0f,0.0f,
  0.5f * sideLength,-0.5f * sideLength, 0.5f * sideLength,  0.0f,-1.0f, 0.0f, 1.0f,0.0f,
 
 -0.5f * sideLength,-0.5f * sideLength, 0.5f * sideLength,  0.0f,-1.0f, 0.0f, 0.0f,0.0f,
 -0.5f * sideLength,-0.5f * sideLength,-0.5f * sideLength,  0.0f,-1.0f, 0.0f, 0.0f,1.0f,
 -0.5f * sideLength, 0.5f * sideLength,-0.5f * sideLength,  0.0f, 1.0f, 0.0f, 0.0f,1.0f,
  0.5f * sideLength, 0.5f * sideLength,-0.5f * sideLength,  0.0f, 1.0f, 0.0f, 1.0f,1.0f,
 

  0.5f * sideLength, 0.5f * sideLength, 0.5f * sideLength,  0.0f, 1.0f, 0.0f, 1.0f,0.0f,
  0.5f * sideLength, 0.5f * sideLength, 0.5f * sideLength,  0.0f, 1.0f, 0.0f, 1.0f,0.0f,
 -0.5f * sideLength, 0.5f * sideLength, 0.5f * sideLength,  0.0f, 1.0f, 0.0f, 0.0f,0.0f,
 -0.5f * sideLength, 0.5f * sideLength,-0.5f * sideLength,  0.0f, 1.0f, 0.0f, 0.0f,1.0f
};
	m_VBO = std::make_unique<VBO>(vertices, sizeof(vertices));
	VBOLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(3);
	layout.Push<float>(2);
	m_VAO = std::make_unique<VAO>();
	m_VAO->AddBuffer(*m_VBO, layout);
	m_Texture = std::make_unique<Texture>("assets/textures/container.jpg");
	m_Shader = std::make_unique<Shader>("assets/shaders/vertex.vert" ,"assets/shaders/fragment.frag");
	//m_Texture->Bind();
	m_Shader->Bind();
	//m_Shader->SetUniform1i("u_Texture", 0); // 0 is slot number. it should match with slot we chose
	updateUniforms();

}

Cube::~Cube()
{
}

void Cube::draw()
{
	//m_Texture->Bind();
	m_Shader->Bind();
	//m_Shader->SetUniform1i("u_Texture", 0); // 0 is slot number. it should match with slot we chose
	updateUniforms();
	GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
}
void Cube::updateUniforms() {
	m_Shader->Bind();
	m_Shader->SetUniform3fv("objectColor", m_CubeColor);
	m_Shader->SetUniform3fv("lightColor", m_LightColor);
	m_Shader->SetUniform3fv("lightPos", m_LightPos);
	m_Shader->SetUniform3fv("viewPos", Scene::instancePtr->getCameraPosition());
	m_Shader->setUniformMat4f("model", m_Model);
	m_Shader->setUniformMat4f("view", m_View);
	m_Shader->setUniformMat4f("projection", m_Proj);

	
}
void Cube::Rotate(float degree , glm::vec3& axis) {
	m_Model = glm::rotate(m_Model, glm::radians(-m_Degree), m_Axis);
	m_Degree = degree, m_Axis = axis;
	m_Model = glm::rotate(m_Model, glm::radians(m_Degree), m_Axis);
}
void Cube::Translate(glm::vec3& translate) {
	m_Model = glm::translate(m_Model, -m_Translate);
	m_Translate = translate;
	m_Model = glm::translate(m_Model, m_Translate);
}
void Cube::Scale(glm::vec3& scale) {
	m_Model = glm::scale(m_Model, glm::vec3(1.0f, 1.0f, 1.0f) / m_Scale);
	m_Scale = scale;
	m_Model = glm::scale(m_Model, m_Scale);
}
void Cube::Scale(float scale) {
	m_Model = glm::scale(m_Model, glm::vec3(1.0f / m_FScale, 1.0f / m_FScale, 1.0f / m_FScale));
	m_FScale = scale;
	m_Scale = glm::vec3(m_FScale, m_FScale, m_FScale);
	m_Model = glm::scale(m_Model,m_Scale);
}
//void Cube::RotateAroundAxis(float angle, const glm::vec3& axis, const glm::vec3& pivot) {
//	// Translate to the pivot point
//	m_Model = glm::translate(m_Model, pivot);
//
//	// Apply rotation around the given axis
//	m_Model = glm::rotate(m_Model, glm::radians(angle), axis);
//
//	// Translate back to the original position
//	m_Model = glm::translate(m_Model, -pivot);
//}


void Cube::SetView(glm::mat4 view) {
	//m_View = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -400.0f))* view;
	m_View = view;
	updateUniforms();
}
void Cube::SetProj(glm::mat4 proj) {
	//m_View = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -400.0f))* view;
	m_Proj = proj;
	updateUniforms();
}
void Cube::RotateAroundAxis(float angle, const glm::vec3& axis, const glm::vec3& pivot) {
	// Step 1: Translate cube so that pivot becomes the origin
	m_Model = glm::translate(glm::mat4(1.0f), -pivot) * m_Model;

	// Step 2: Rotate around the world-space axis
	m_Model = glm::rotate(glm::mat4(1.0f), glm::radians(angle), axis) * m_Model;

	// Step 3: Translate cube back to its original position
	m_Model = glm::translate(glm::mat4(1.0f), pivot) * m_Model;
}
