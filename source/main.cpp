#include "Game.h"
#include <eng.h>

int main()
{
	Game* game = new Game();
	engine::Engine& engine = engine::Engine::GetInstance();

	engine.SetApplication(game);

	if (engine.Init(1280, 720))
	{
		engine.Run();
	}

	engine.Destroy();

	return 0;
}