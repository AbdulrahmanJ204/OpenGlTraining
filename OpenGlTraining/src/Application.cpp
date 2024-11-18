#include<Application.h>

Application::Application()
{

	spdlog::info("Starting Application");
	if (glfwIniti()) {
		return;
	}

	m_TestsMenu = new test::TestMenu(m_CurrentTest);
	m_CurrentTest = m_TestsMenu;
	m_TestsMenu->AddTest<test::TestClearColor>("Clear Color");
	m_TestsMenu->AddTest<test::TestTexture2D>("2D Texture");
	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	myImGuiManager myImGui(window, m_Width, m_Height);
	while (!glfwWindowShouldClose(window)) {
		processInput();
		m_Renderer.Clear();
		GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		glfwPollEvents();
		LoadImGui(myImGui);
		glfwSwapBuffers(window);
	}

}

void Application::LoadImGui(myImGuiManager& myImGui)
{
	myImGui.BeginFrame();
	if (m_CurrentTest) {
		m_CurrentTest->OnUpdate(0.0f);
		m_CurrentTest->OnRender();
		ImGui::Begin("Test");
		if (m_CurrentTest != m_TestsMenu && ImGui::Button("<-")) {
			delete	m_CurrentTest;
			m_CurrentTest = m_TestsMenu;
		}
		m_CurrentTest->OnImGuiRender();
		ImGui::End();
	}
	myImGui.EndFrame();
}

Application::~Application()
{

	delete m_TestsMenu;
	if (m_TestsMenu != m_CurrentTest) {
		delete m_CurrentTest;
	}

	glfwDestroyWindow(window);
	glfwTerminate();

}

float Application::getRandom()
{
	return (float)(rand() % 100) / 100;
}

int Application::glfwIniti()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	window = glfwCreateWindow(m_Width, m_Height, "OPEN GL", NULL, NULL);

	if (window == NULL) {
		spdlog::error("Failed to create GLFW window");
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	// glad: load all OpenGL function pointers
// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		spdlog::error("Failed to initialize GLAD");
		return -1;
	}
	return 0;
}

void Application::processInput()

{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		
	}
}





