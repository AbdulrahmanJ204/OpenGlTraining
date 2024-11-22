#pragma once
#include <VBO.h>
#include <Shader.h>
#include <EBO.h>
#include <VAO.h>
#include <memory>
#include <Texture.h>

#include<glm/glm.hpp>	
#include<glm/gtc/matrix_transform.hpp>

class Cube
{
private:
	std::unique_ptr< VAO >m_VAO;
	std::unique_ptr< VBO >m_VBO;
	std::unique_ptr< Shader >m_Shader;
	std::unique_ptr< Texture >m_Texture;
	float m_Length , m_Degree, m_FScale;
	glm::mat4 m_Proj, m_View, m_Model, m_MVP;
	glm::vec3 m_Axis , m_Translate , m_Scale;
	
public:
	Cube(float sideLength);
	~Cube();
	void draw();
	void Rotate(float degree, glm::vec3& axis);
	void Translate(glm::vec3& translate);
	void Scale(glm::vec3& scale);
	void Scale(float scale);
	void SetView(glm::mat4 view);
	void RotateAroundAxis(float angle, const glm::vec3& axis, const glm::vec3& pivot);
};

