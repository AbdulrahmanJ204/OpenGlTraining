#pragma once
#include "core.h"
#include "cube.h"
#include "Camera.h"
#include "model.h"
class Scene
{
public:
	Scene();
	~Scene();
	void render();
	inline glm::vec3 getCameraPosition() const { return camera.Position; }
	inline float& getRotation()  {return m_Rotation;}
	inline Camera& getCamera() { return camera; };

	void onCursorPositionEvent(double x, double y);
	void processDiscreteInput(int32_t key, int32_t scancode, int32_t action, int32_t mode, float deltaTime);
	void processContinuousInput(float& deltaTime);



	static Scene* instancePtr;
private:
	Camera camera;
	Model m_Model;
	Shader modelShader;
	float lastX, lastY;
	bool firstMouse;
	//Cube m_Cube;
	float m_Rotation = 0.0f;
	glm::mat4 m_Proj, m_View;
};

