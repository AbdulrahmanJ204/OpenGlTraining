#include<Application.h>

// TODO: - test rotating on the origin , not the corner
// TODO: - test scaling , add slider to test it
// TODO: check why order matters , maybe from chatgpt

class Main {
public:
	static GLFWwindow* window;
};
GLFWwindow* Main::window = nullptr; 
int main() {
	auto app = Application();
	Main::window = Application::window;
	return 0;
}