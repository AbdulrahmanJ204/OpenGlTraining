//// ------for APIENTRY Warnings-----
//#define WIN32_LEAN_AND_MEAN
//#define NOMINMAX
//// --------------------------------
#include"Application.h"
#include<memory>
// todo: - test rotatearoundaxis in cube class , and understand how to control it .
// todo: - check build output , why all that stuff is there.
// todo: check why order matters , maybe from chatgpt


// TODO: - open chatgpt to last conversation , and implement Window class and Camera Class.

int main() {
	std::unique_ptr<Application> app = std::make_unique<Application>() ;
	app->run();
	return 0;
}