#pragma once
#include <VertexBuffer.h>
#include <Shader.h>
#include <IndexBuffer.h>
#include <VertexArray.h>
#include <memory>
#include <Texture.h>

#include<glm/glm.hpp>	
#include<glm/gtc/matrix_transform.hpp>

class Cube
{
private:
	std::unique_ptr< VertexArray >m_VAO;
	std::unique_ptr< VertexBuffer >m_VBO;
	std::unique_ptr< IndexBuffer >m_EBO;
	std::unique_ptr< Shader >m_Shader;
	std::unique_ptr< Texture >m_Texture;
	float m_Length;
	glm::mat4 m_Proj, m_View, m_Model, m_MVP;
public:
	Cube(float sideLength);
	~Cube();
	void draw();
};

