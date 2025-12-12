#pragma once

#include <string>
#include <vector>
#include "AppState.h"
#include "WrappedText.h"
#include "Constants.h"
#include "CursesWrapper.h"

// Renderer is responsible for all rendering-related tasks using ncurses.
class Renderer
{
    public:
        Renderer() = default;
        ~Renderer() { Curses::endwin();}

    public:
        void Initialize();      
        void UpdateScreen(AppStateManager& state);
        void Resize();
        void StopRendering() { Curses::endwin(); }
        int GetCols() const { return COLS; }

    private:
        void RedrawText(AppStateManager& state);
};

