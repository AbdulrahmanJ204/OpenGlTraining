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
	std::unique_ptr< Texture >m_SpMap;
	float m_Length , m_Degree, m_FScale;
	glm::mat4 m_Proj, m_View, m_Model;

	glm::vec3 m_Axis  , m_Pos, m_Translate , m_Scale , m_CubeColor , m_LightColor, m_LightPos;
	
public:
	Cube();
	Cube(float sideLength , const std::string& vertexPath , const std::string& fragPath , glm::vec3 trans = glm::vec3(0.0f , 0.0f , 0.0f) );

	// Allow moving
	Cube(Cube&&) noexcept = default;
	Cube& operator=(Cube&&) noexcept = default;
	~Cube();
	void draw();
	void updateUniforms();
	void Rotate(float degree, glm::vec3& axis);
	void Translate(glm::vec3& translate);
	void Scale(glm::vec3& scale);
	void Scale(float scale);
	void SetView(glm::mat4 view);
	void SetProj(glm::mat4 proj);
	void SetLightPos(glm::vec3 pos);
	void RotateAroundAxis(float angle, const glm::vec3& axis, const glm::vec3& pivot);

	inline glm::vec3 getPos() const { return m_Pos; }
	inline glm::vec3 getLightPos() const { return m_LightPos; }
};

