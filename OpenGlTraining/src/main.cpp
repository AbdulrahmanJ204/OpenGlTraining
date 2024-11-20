// ------for APIENTRY Warnings-----
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
// --------------------------------
#include<Application.h>

// TODO: - test RotateAroundAxis in Cube class , and understand how to control it .
// TODO: - check build output , why all that stuff is there.
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