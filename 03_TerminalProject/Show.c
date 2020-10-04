#include <ncurses.h>

#define DX 3

typedef struct File {
    char* Text;
} File;

void show_console(const char *filename)
{
    WINDOW *win;
    int c = 0;

    initscr();
    noecho();
    cbreak();
    printw("File: %s;", filename);
    refresh();

    int width = COLS - 2 * DX;
    int height = LINES - 2 * DX;

    win = newwin(height, width, DX, DX);
    keypad(win, TRUE);
    curs_set(0);
    do {
        werase(win);
        wmove(win, 1, 0);

        wprintw(win, "  Key: %d, Name: %s\n", c, keyname(c));

        
        box(win, 0, 0);
        wrefresh(win);
    } while((c = wgetch(win)) != 27);

    endwin();
}

int main(int argc, char **argv)
{
    if(argc < 2) {
        printf("few arguments\n");
        return -1;
    }

    show_console(argv[1]);

	return 0;
}
