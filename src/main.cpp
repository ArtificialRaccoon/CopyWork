#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

#include "Constants.h"
#include "AppState.h"
#include "Renderer.h"

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
		return 1;
	}

	Renderer renderer;
	renderer.Initialize();

	AppStateManager state;
	std::string filename = argv[1];
	if (!state.Initialize(filename, renderer.GetCols()))
	{
		std::cerr << "Failed to initialize application state." << std::endl;		
		return 1;
	}
	
	renderer.UpdateScreen(state);

	int ch;
	while ((ch = getch()) != KEY_ESC)
	{
		switch (ch)
		{
			case KEY_RESIZE:
				renderer.Resize();
				state.Resize(renderer.GetCols());
				break;
			case KEY_BACKSPACE:
			case KEY_BACKSPACE_ALT_DEL:
			case KEY_BACKSPACE_ALT_BS:
				state.Backspace();
				break;
			default:
				state.CheckInput(ch);
				break;
		}
		renderer.UpdateScreen(state);
	}

	state.SaveState();
}