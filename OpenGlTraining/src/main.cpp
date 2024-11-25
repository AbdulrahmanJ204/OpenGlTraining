#include"Application.h"


// todo: - check build output , why all that stuff is there. // for cube i guess.

int main() {
	std::unique_ptr<Application> app = std::make_unique<Application>() ;
	app->run();
	return 0;
}