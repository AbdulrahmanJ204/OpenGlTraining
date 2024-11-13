#pragma once
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
class Renderer {
public:
	Renderer();
	~Renderer();
	void Clear();
	void Draw(VertexArray& va, IndexBuffer& ib, Shader& shader);
};

