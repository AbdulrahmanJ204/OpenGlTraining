#pragma once
#include "core.h"
#include "cube.h"
#include "ModelObject.h"
#include "Camera.h"
#include "model.h"
class Scene
{
public:
	Scene();
	~Scene();
	void render();
	inline glm::vec3& getCameraPosition() { return camera.Position; }
	inline glm::vec3& getLightPosition() { return m_LightPos; }
	inline float& getRotation() { return m_Rotation; }
	inline float& getScale() { return m_Scale; }
	inline Camera& getCamera() { return camera; };

	void onCursorPositionEvent(double x, double y);
	void processDiscreteInput(int32_t key, int32_t scancode, int32_t action, int32_t mode, float deltaTime);
	void processContinuousInput(float& deltaTime);



	static Scene* instancePtr;
private:
	
	Camera camera;
	float lastX, lastY;
	bool firstMouse;
	//Cube m_Cube;
	Cube  m_LightCube;
	glm::vec3 m_LightPos;
	float m_Rotation = 0.0f, m_Scale = 1.0f;
	glm::mat4 m_Proj, m_View;
	glm::vec3 cubePositions[10];
	Cube cubes[10];
	ModelObject modelObj;
};

