#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

#define DX 3

#define KEY_SPACE 32
#define KEY_ESC   27

int min(int x, int y) {
    return x < y ? x : y;
}

int max(int x, int y) {
    return x < y ? y : x;
}

typedef struct File {
    int file_exist;
    int number_lines;
    char* filename;
    char** lines;
} File;

void free_file(File file) {
	for (int i = 0; i < file.number_lines; ++i)
	{
		free(file.lines[i]);
	}
	free(file.lines);
}

char *read_line(FILE *ptrFile)
{
    int fgetcResult = fgetc(ptrFile);

    if(EOF == fgetcResult) {
        return NULL;
    }

    int size_buffer_line = 30;
    char *line = (char*) malloc(size_buffer_line);
    int pos = 0;

    while((EOF != fgetcResult) && ('\n' != fgetcResult)) {
        if (pos + 2 >= size_buffer_line) {
            size_buffer_line *= 2;
            line = (char *) realloc(line, size_buffer_line*sizeof(char));
        }
        line[pos++] = (char) fgetcResult;
        fgetcResult = fgetc(ptrFile);
    }
    line[pos] = 0;
    return line;
}

File read_file(char* filename)
{
    File file;
    file.filename = filename;
    FILE *ptrFile = fopen(file.filename, "r");
    if(ptrFile == NULL) {
        printf("File %s not exist \n", file.filename);
        file.file_exist = 0;
        return file;
    }
    file.file_exist = 1;
    int size_buffer_lines = 30;
    char **lines = (char **) malloc(size_buffer_lines * sizeof(char*));
    int number_cur_line = 0;
    int flagEOF = 0;
    do {
        if (number_cur_line >= size_buffer_lines) {
            size_buffer_lines *= 2;
            lines = (char **) realloc(lines, size_buffer_lines*sizeof(char*));
        }
    } while((lines[number_cur_line++] = read_line(ptrFile)) != NULL);

    file.number_lines = number_cur_line - 1;
    file.lines = lines;
    return file;
}

void show_console(File file)
{
    WINDOW *win;
    int key = 0;

    initscr();
    noecho();
    cbreak();
    printw("File: %s; size: %d", file.filename, file.number_lines);
    refresh();

    int width = COLS - 2 * DX;
    int height = LINES - 2 * DX;

    win = newwin(height, width, DX, DX);
    keypad(win, TRUE);
    curs_set(0);

    int view_width = width - 2;
    int view_height = height - 2;
    

    int top_line_number = 0;
    int bottom_line_number = min(view_height, file.number_lines);
    int left_column_number = 0;
    do {
        werase(win);
        wmove(win, 1, 0);

        switch (key)
        {
            case KEY_UP:
                top_line_number = max(top_line_number - 1, 0);
                bottom_line_number = max(bottom_line_number - 1, min(view_height, file.number_lines));
                break;
            case KEY_DOWN:
            case KEY_SPACE:
                top_line_number = min(top_line_number + 1, file.number_lines - view_height);
                bottom_line_number = min(bottom_line_number + 1, file.number_lines);
                break;
            case KEY_RIGHT:
                left_column_number++;
                break;
            case KEY_LEFT:
                left_column_number = max(left_column_number - 1, 0);
                break;
            default:
                break;
        }

        char output_line[width - 6];
        output_line[width - 7] = 0;
        for(int i = top_line_number; i < bottom_line_number; i++) {
            wprintw(win, " %3d: ", i + 1);
            strncpy(output_line, file.lines[i] + left_column_number, width - 7);
            wprintw(win, "%s\n", output_line);
        } 

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

    File file = read_file(argv[1]);
    if (file.file_exist) {
        show_console(file);
    }

    free_file(file);
	return 0;
}