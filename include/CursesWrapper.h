#pragma once

#if defined(_WIN32) || defined(_WIN64)
#include <curses.h>
#else
#include <ncurses.h>
#endif

/*
* A simple wrapper namespace around ncurses functions to provide a clear interface (IMO).
*/
namespace Curses
{
    inline void initscr() { ::initscr(); }
    inline void start_color() { ::start_color(); }
    inline void init_pair(short pair, short f, short b) { ::init_pair(pair, f, b); }
    inline void wrapped_attron(int attrs) { ::attron(attrs); }
    inline void wrapped_attroff(int attrs) { ::attroff(attrs); }
    inline void wrapped_mvaddch(int y, int x, const chtype ch) 
    {
#if defined(_WIN32) || defined(_WIN64)
        ::mvaddch(y, x, ch);
#else
        mvaddch(y, x, ch);
#endif                 
    }
    inline void clear() { ::clear(); }
    inline void cbreak() { ::cbreak(); }
    inline void noecho() { ::noecho(); }
    inline void keypad(WINDOW* win, bool bf) { ::keypad(win, bf); }
    inline void curs_set(int visibility) { ::curs_set(visibility); }
    inline void refresh() { ::refresh(); }
    inline void wclear(WINDOW* win) { ::wclear(win); }
    inline void wrefresh(WINDOW* win) { ::wrefresh(win); }
    inline void move(int y, int x) { ::move(y, x); }
    inline void endwin() { ::endwin(); }
    inline void resize_term(int lines, int cols) { ::resize_term(lines, cols); }
    inline int COLORPAIR(int n) { return COLOR_PAIR(n); }
}
