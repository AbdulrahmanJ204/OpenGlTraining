#pragma once
#include "core.h"
#include "cube.h"
#include "Camera.h"
class Scene
{
public:
	Scene();
	~Scene();
	void onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode, float deltaTime);
	void render();
	inline float& getRotation()  {return m_Rotation;}


private:
	Cube m_Cube;
	Camera camera;
	float m_Rotation = 0.0f;
	glm::mat4 m_Proj, m_View;
};

