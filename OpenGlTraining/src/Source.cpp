
#include<iostream>
#include<spdlog/spdlog.h>

#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include<fstream>
#include<string>

#include<intrin.h>

#include"Renderer.h"

#include"VertexBuffer.h"
#include"IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"

float getRandom() {
	float number = (float)(rand() % 100) / 100;

	//std::cout << "Rand  = " << number << std::endl;
	return number;
}
int main() {
	//srand(time(0));
	spdlog::info("Hello!");
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 800, "OPEN GL", NULL, NULL);

	if (window == NULL) {
		std::cout << "Failed !" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	float vertices1[] = {
		-0.8f, -0.4f, 1.0f , 0.0f, 0.3f , 1.0f,
		 -0.01f, -0.4f, 0.0f, 1.0f, 0.0f , 1.0f,
		 -0.01f, 0.4f,  0.0f, 0.0f , 1.0f ,1.0f
	};
	//float vertices1[] = {
	//	-0.95f, -0.95f, 0.0f , 0.0f, 1.0f , 1.0f,
	//	 0.95f, 0.0f, 0.0f, 0.0f, 1.0f , 1.0f,
	//	 -0.95f, 0.95f,  0.0f, 0.0f , 1.0f ,1.0f
	//};
	float vertices2[] = {
		 0.01f , -0.4f,1.0f , 0.5f, 0.3f , 1.0f,
		 0.8f , -0.4f, 0.5f, 0.3f , 1.0f ,1.0f,
		 0.01f , 0.4f,0.5f, 1.0f, 0.3f , 1.0f
	};

	unsigned int indices[] = {
		0, 1, 2,
	};
	IndexBuffer ib(indices, 3);


	VertexBuffer vertexBuffer(vertices1, sizeof(vertices1));
	VertexArray va1;
	VertexBufferLayout layout;
	layout.Push<float>(2);
	layout.Push<float>(4);
	va1.AddBuffer(vertexBuffer, layout);
	ib.Bind();
	va1.Unbind();
	ib.Unbind();

	VertexBuffer vb2(vertices2, sizeof(vertices2));
	VertexArray va2;
	VertexBufferLayout  layout2 = layout;
	va2.AddBuffer(vb2, layout2);
	ib.Bind();



	Shader UniformShader("res/shaders/Uniform.shader");
	Shader OutInShader("res/shaders/OutIn.shader");
	va2.Unbind();
	ib.Unbind();

	float r = 0.5f;
	float increament = 0.05f;

	//GLCall(glClearColor(1.0f, 1.0f, 1.0f, 0.9f));
	while (!glfwWindowShouldClose(window)) {
		GLCall(glClear(GL_COLOR_BUFFER_BIT));




		// draw left tri
		va1.Bind();
		UniformShader.Bind();
		UniformShader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);

		//GLCall(glDrawArrays(GL_TRIANGLES, 0, 3));
		GLCall(glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr));

		// draw right tri
		va2.Bind();
		OutInShader.Bind();
		GLCall(glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr));
		//GLCall(glDrawArrays(GL_TRIANGLES, 0, 3));


		if (r > 1.0 || r < 0.0) {
			increament *= -1;
		}
		r += increament;
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
