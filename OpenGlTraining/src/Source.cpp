
#include<iostream>
#include<fstream>
#include<string>
#include<spdlog/spdlog.h>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<intrin.h>

#include"Renderer.h"

#include"VertexBuffer.h"
#include"IndexBuffer.h"
#include "VertexArray.h"


struct ShaderSource {
	std::string vertexSource;
	std::string FragmentSource;
};


ShaderSource ParseShader(const std::string& filePath) {
	std::fstream stream(filePath);
	std::string line;
	enum class Type {
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};
	Type type = Type::NONE;
	std::string s[2] = { "","" };
	while (getline(stream, line)) {
		if (line.find("#shader") != std::string::npos) {
			if (line.find("vertex") != std::string::npos) {
				type = Type::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos) {
				type = Type::FRAGMENT;
			}
		}
		else {
			s[(int)type] += line + "\n";
		}
	}

	return { s[0] , s[1] };
}

static unsigned int compileShader(unsigned int type, const std::string source) {
	int id = glCreateShader(type);
	// making a pointer to the beggining of the string:
	const char* src = source.c_str();
	// shader , how many shaders , source id , end of shader if you dont want to compile the whole string.
	glShaderSource(id, 1, &src, nullptr); // specifies the source of shader

	// compile it
	glCompileShader(id);

	// Error Handling
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);

	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)_malloca(length * sizeof(char)); // dynamicly store char array in stack : just skip it.
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Faild to compile " << (type == GL_VERTEX_SHADER ? "vertex " : "fragment ") << " shader!\n";
		std::cout << message << std::endl;

		glDeleteShader(id);
		return 0;
	}
	return id;

}
static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
	unsigned int program = glCreateProgram();
	unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

	// attach shaders to program
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	// link program
	glLinkProgram(program);
	glValidateProgram(program);

	// delete intermidate data 
	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}


float getRandom() {
	float number =(float) ( rand() % 100)/100;
	
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

	VertexBuffer vb2(vertices2, sizeof(vertices2));	
	VertexArray va2;
	VertexBufferLayout  layout2 = layout;
	va2.AddBuffer(vb2 , layout2);
	ib.Bind();
	

	
	ShaderSource shaderSource = ParseShader("res/shaders/Basic.shader");
	unsigned int shader = CreateShader(shaderSource.vertexSource, shaderSource.FragmentSource);
	glUseProgram(shader);
	
	va2.Unbind();
	ib.Unbind();
	//int location;
	//GLCall(location = glGetUniformLocation(shader, "u_Color"));
	//ASSERT(location != -1);
	//	//GLCall(glUniform4f(location, r, 0.3, 0.8, 1.0f));
	float r = 0.5f;
	float increament = 0.005f;

	//GLCall(glClearColor(1.0f, 1.0f, 1.0f, 0.9f));
	while (!glfwWindowShouldClose(window)) {
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

	
		

		// draw left tri
		va1.Bind();
	
		//GLCall(glDrawArrays(GL_TRIANGLES, 0, 3));
		GLCall(glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr));

		//GLCall(glUniform4f(location, r, 0.3, 0.8, 1.0f));
		//GLCall(glUniform4f(location, getRandom(), getRandom(), getRandom(), 1.0f));
		
		// draw right tri
		va2.Bind();
		GLCall(glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr));
		//GLCall(glDrawArrays(GL_TRIANGLES, 0, 3));

		//GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

		//if (r > 1.0 || r < 0.0) {
		//	increament *= -1;
		//}
		//r += increament;
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteProgram(shader);
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
