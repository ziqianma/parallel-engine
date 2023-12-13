#include "Core/core.h"

int main()
{
	Core::Renderer renderer;
	Core::Application application(800, 600);
	application.init(renderer);
	return 0;
}