#include "GLErrorManager.h"

#include<iostream>	
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

 void GLClearError() {
	while (glGetError() != GL_NO_ERROR);
}
 bool GLLogCall(const char* function, const char* file, int line) {

	while (GLenum error = glGetError()) {
		std::cout << "[OpenGl Error] (" << error << "): " << function << " ### " << file << " | Line : " << line << std::endl;
		return false;
	}
	return true;
}

 void Draw(VertexArray& va, IndexBuffer& ib, Shader& shader)
 {
	 va.Bind();
	 ib.Bind();
	 shader.Bind();
	 GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
 }
