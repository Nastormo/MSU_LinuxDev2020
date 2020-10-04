#include <ncurses.h>

#define DX 3

#define KEY_SPACE 32
#define KEY_ESC   27

typedef struct File {
    char* Text;
} File;

File read_file(const char* filename)
{

}

void show_console(const char* filename)
{
    WINDOW *win;
    int key = 0;

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

        switch (key)
        {
            case KEY_UP:
            case KEY_DOWN:
            case KEY_SPACE:
            case KEY_RIGHT:
            case KEY_LEFT:
        }

        wprintw(win, "  Key: %d, Name: %s\n; COL: %d, LINES: %d", key, keyname(key), COLS, LINES);


        box(win, 0, 0);
        wrefresh(win);
    } while((key = wgetch(win)) != KEY_ESC);

    endwin();
}

int main(int argc, char **argv)
{
    if(argc < 2) {
        printf("few arguments\n");
        return -1;
    }

    read_file(argv[1]);
    show_console(argv[1]);

	return 0;
}
