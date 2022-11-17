#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "pch.h"

void execute();
int main(int argc, char* argv[]) // Entry Point
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	execute();
	std::cout << "";
}
void execute() // All code to excute (for CRT detect memory leak and VS heap snapshot)
{
	Game* game = Game::GetInstance();

	(*game).Init();
	(*game).Run();
	(*game).Quit();
}



