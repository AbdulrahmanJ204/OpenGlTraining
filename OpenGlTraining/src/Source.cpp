
#include<iostream>
#include<spdlog/spdlog.h>

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>	
#include<glm/gtc/matrix_transform.hpp>


#include"GLErrorManager.h"
#include"VertexBuffer.h"
#include"IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Renderer.h"
#include "Texture.h"

float getRandom() {
	float number = (float)(rand() % 100) / 100;

	//std::cout << "Rand  = " << number << std::endl;
	return number;
}
void changeColors(float  increament[3], float& r, float& g, float& b)
{
	if (r > 1.0 || r < 0.0) {
		increament[0] *= -1;
		//r = getRandom();
	}
	r += increament[0];
	if (g > 1.0 || g < 0.0) {
		increament[1] *= -1;
		//g = getRandom();
	}
	g += increament[1];
	if (b > 1.0 || b < 0.0) {
		increament[2] *= -1;
		//b = getRandom();
	}
	b += increament[2];
}
int main() {
	//srand(time(0));
	spdlog::info("Hello!");
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	
	int width = 800, height = 800;
	GLFWwindow* window = glfwCreateWindow(width, height, "OPEN GL", NULL, NULL);

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

	// for now, should be disabled when you want to blend transeperant objects, 
	// you could enable it before 3D object , then disable it when rendering the transparents
	// consider the order of drawing , where last darw will be on top.
	//glEnable(GL_DEPTH_TEST);

	//float vertices1[] = {
	//	-0.8f, -0.4f , 0.1f,      1.0f , 0.0f, 0.3f , 1.0f,
	//	 -0.01f, -0.4f ,0.1f,    0.0f, 1.0f, 0.0f , 1.0f,
	//	 -0.01f, 0.8f , 0.1f,     0.0f, 0.0f , 1.0f ,1.0f
	//};
		float vertices1[] = {
		100.0f, 100.0f , -10.0f,      1.0f , 0.0f, 0.3f , 1.0f,
		 500.0f, 100.0f ,-10.0f,    0.0f, 1.0f, 0.0f , 1.0f,
		 300.0f, 400.0f , -10.0f,     0.0f, 0.0f , 1.0f ,1.0f
	};
	//float vertices1[] = {
	//	-0.95f, -0.95f, 0.0f , 0.0f, 1.0f , 1.0f,
	//	 0.95f, 0.0f, 0.0f, 0.0f, 1.0f , 1.0f,
	//	 -0.95f, 0.95f,  0.0f, 0.0f , 1.0f ,1.0f
	//};
	// 
	//float vertices2[] = {
	//	 -0.4f , -0.4f,	0.0f,	 1.0f , 0.5f, 0.3f , 1.0f,
	//	 0.8f , -0.4f,0.0f,	0.5f, 0.3f , 1.0f ,1.0f,
	//	 0.01f , 0.4f,	0.0f,	 0.5f, 1.0f, 0.3f , 1.0f
	//};
	float vertices2[] = {
	 300.0f , 100.0f,	-1.0f,		 1.0f , 0.5f, 0.3f , 1.0f,
	 700.0f , 100.0f,	-1.0f,			0.5f, 0.3f , 1.0f ,1.0f,
	 500.0f , 400.0f,	-1.0f,		 0.5f, 1.0f, 0.3f , 1.0f
	};
	unsigned int indices[] = {
		0, 1, 2,
	};
	IndexBuffer ib(indices, 3);
	ib.Bind();


	VertexBuffer vertexBuffer(vertices1, sizeof(vertices1));
	VertexArray va1;
	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(4);
	va1.AddBuffer(vertexBuffer, layout);

	VertexBuffer vb2(vertices2, sizeof(vertices2));
	VertexArray va2;
	VertexBufferLayout  layout2;
	layout2.Push<float>(3);
	layout2.Push<float>(4);
	va2.AddBuffer(vb2, layout2);

	

	Shader UniformShader("res/shaders/Uniform.shader");
	Shader OutInShader("res/shaders/OutIn.shader");

	float r = 0.8f;
	float g = 0.5f;
	float b = 0.2f;
	float increament[] = { 0.02f  , -0.01f , 0.03f };
	float verticesForTextures[] = {
		-0.5f, -0.5f ,-0.2f ,		0.0f , 0.0f, // position , textures
		 0.5f, -0.5f ,-0.2f,		1.0f , 0.0f ,
		 0.5f,  0.5f ,-0.2f ,		1.0f , 1.0f ,
	    -0.5f,  0.5f ,-0.2f ,		0.0f , 1.0f ,
	};
	unsigned int indices2[] = {
		0 , 1, 2,
		2 ,3 ,0
	};
	VertexBuffer vbo(verticesForTextures, sizeof(verticesForTextures));
	VertexArray vao;
	VertexBufferLayout layout3;
	layout3.Push<float>(3);
	layout3.Push<float>(2);
	vao.AddBuffer(vbo, layout3);
	IndexBuffer ib2(indices2, 6);

	Texture texture("res/textures/a10.png");
	texture.Bind();

	Shader TextureShader("res/shaders/texture.shader");
	TextureShader.Bind();
	TextureShader.SetUniform1i("u_Texture", 0); // 0 is slot number. it should match with slot we chose
	
	glm::mat4 proj = glm::ortho(0.0f, width * 1.0f, 0.0f, height *1.0f,0.0f, 100.0f);
	glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-50 , 0 , 0)); // represents camera , move the whole world in reverse direction of your movement
	glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(100 , 100 , 0)); // represents camera , move the whole world in reverse direction of your movement
	glm::mat4 mvp = proj * view * model; // think of multplication as from right to left , read more about matrices productoin in opengl , and arrays row and column stuff
	GLCall(glEnable(GL_BLEND));
	
	TextureShader.setUniformMat4f("u_MVP", mvp);
	UniformShader.Bind();
	UniformShader.setUniformMat4f("u_MVP", mvp);
	OutInShader.Bind();
	OutInShader.setUniformMat4f("u_MVP", mvp);
	Renderer renderer;
	GLCall(glClearColor(1.0f, 1.0f, 1.0f, 0.9f));
	while (!glfwWindowShouldClose(window)) {

		renderer.Clear();

	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
		//GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE));
		// draw left tri
		UniformShader.Bind();

		UniformShader.SetUniform4f("u_Color", r, g, b, 0.7f);
		//UniformShader.SetUniform4f("u_Color", 1.0f, 0.0f, 0.0f, 0.9f);
		renderer.Draw(va1, ib, UniformShader);
		// draw right tri

		UniformShader.SetUniform4f("u_Color", g, b, r, 0.7f);
		//UniformShader.SetUniform4f("u_Color", 0.0f, 0.0f, 1.0f, 0.9f);
		renderer.Draw(va2, ib, UniformShader);
		//renderer.Draw(va2, ib, OutInShader);

		TextureShader.Bind();
		renderer.Draw(vao, ib2, TextureShader);
		changeColors(increament, r, g, b);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
