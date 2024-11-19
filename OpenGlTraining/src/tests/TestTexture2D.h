#pragma once
#include "Test.h"
#include "VertexArray.h"
#include "Shader.h"
#include "IndexBuffer.h"
#include "Texture.h"
#include "Application.h"

#include<glm/glm.hpp>	
#include<glm/gtc/matrix_transform.hpp>

#include<memory>	

namespace test {
	class TestTexture2D : public Test
	{
	private:
		std::unique_ptr< VertexArray >m_VAO;
		std::unique_ptr< VertexBuffer >m_VBO;
		std::unique_ptr< IndexBuffer >m_EBO;
		std::unique_ptr< Shader >m_Shader;
		std::unique_ptr< Texture >m_Texture;
		float m_Rotation = 0.0f, m_Rotation2 = 0.0f,
			m_RotaionIncreamnt = 2.0f,
			m_RotaionIncreamnt2 = 2.0f,
			m_Scale = 1.0f;
		glm::mat4 m_Proj, m_View, m_Model, m_MVP;
		glm::vec3 m_Translation, m_Translation2;

	public:
		//float m_Width = Application::m_Width  , m_Height = Application::m_Height;
		TestTexture2D();
		~TestTexture2D();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;




	};
}

