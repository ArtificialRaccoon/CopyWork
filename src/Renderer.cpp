#include "Renderer.h"

void Renderer::Initialize()
{
	Curses::initscr();
	Curses::cbreak();
	Curses::noecho();
	Curses::keypad(stdscr, TRUE);
	Curses::curs_set(1);

	Curses::start_color();
	Curses::init_pair(COLOR_DEFAULT, COLOR_CYAN, COLOR_BLACK);
	Curses::init_pair(COLOR_CORRECT, COLOR_WHITE, COLOR_BLACK);
	Curses::init_pair(COLOR_INCORRECT, COLOR_RED, COLOR_BLACK);
}

void Renderer::RedrawText(AppStateManager& state)
{
	const WrappedText& wrapped = state.GetWrapped();
	const std::vector<CharState>& progress = state.GetProgress();

	int y = 0;
	int x = 0;

	for (size_t i = 0; i < wrapped.text.size(); ++i)
	{
		char c = wrapped.text[i];

		if (c == CHAR_NEWLINE)
		{
			y++;
			x = 0;
			continue;
		}

		if (y < state.GetScrollY())
			continue;

		if (y - state.GetScrollY() >= LINES)
			continue;

		int colorAttr = A_DIM | Curses::COLORPAIR(COLOR_DEFAULT);
		size_t originalIndex = wrapped.originalIndices[i];		

		if (originalIndex != std::string::npos && originalIndex < progress.size())
		{
			if (progress[originalIndex] == STATE_CORRECT)
				colorAttr = A_BOLD | Curses::COLORPAIR(COLOR_CORRECT);
			else if (progress[originalIndex] == STATE_INCORRECT)
				colorAttr = Curses::COLORPAIR(COLOR_INCORRECT);
		}

		Curses::attron(colorAttr);
		Curses::mvaddch(y - state.GetScrollY(), x, c);
		Curses::attroff(colorAttr);

		x++;
	}
}

void Renderer::UpdateScreen(AppStateManager& state)
{
	const WrappedText& wrapped = state.GetWrapped();
	size_t currentPos = state.GetCurrentPos();

	std::pair<int, int> coords = wrapped.GetCursorScreenCoords(currentPos, state.GetScrollY());
	int screenY = coords.first;
	int screenX = coords.second;

	if (screenY >= LINES)
		state.SetScrollY(state.GetScrollY() + (screenY - LINES + 1));
	else if (screenY < 0)
		state.SetScrollY(state.GetScrollY() + screenY);

	coords = wrapped.GetCursorScreenCoords(currentPos, state.GetScrollY());
	screenY = coords.first;
	screenX = coords.second;

	Curses::clear(); 
	RedrawText(state);
	if (screenY != -1 && screenX != -1)
		Curses::move(screenY, screenX);
	Curses::refresh();
}

void Renderer::Resize()
{
	Curses::clear();
	Curses::resize_term(0, 0);
	Curses::wclear(stdscr);
	Curses::wrefresh(stdscr);
}