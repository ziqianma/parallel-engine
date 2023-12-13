#include "Core/core.h"

int main()
{
	Core::SceneNode* scene = NULL;

	Core::Renderer renderer;
	Core::Application application(800, 600, scene);
	application.init(renderer);
	return 0;
}