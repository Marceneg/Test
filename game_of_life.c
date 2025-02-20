#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define height 25
#define width 80
#define speed_min 20000
#define speed_max 200000
#define speed_step 20000

void print_field(int **arr, int rows, int columns, WINDOW *win);
void menu(WINDOW *win);
void change_mode(int mode, int **arr, int rows, int columns, int *speed);
void update(int **arr, int rows, int columns, int speed);
void survive(int **arr, int rows, int columns, int **res);
void revive(int **arr, int rows, int columns, int **res);
void merge(int **sur, int **rev, int rows, int columns, int **res);
int neighb(int **arr, int rows, int columns, int x, int y);
void generate(int **arr, int rows, int columns);
int place_arr(int ***arr, int rows, int columns);
void free_arr(int **arr, int rows);
void make_window(WINDOW *win);
int input_field(int **arr, int rows, int columns, int mode);

int main() {
    clear();
    initscr();
    WINDOW *win = newwin(height + 6, width + 2, 0, 0);
    make_window(win);
    wclear(win);
    int rows = height, columns = width, mode = 0;
    int **data = NULL;
    while (mode != 27) {
        wclear(win);
        box(win, 0, 0);
        menu(win);
        mode = wgetch(win);
        switch (mode) {
            case 10:
                if (place_arr(&data, rows, columns) == 1) {
                    generate(data, rows, columns);
                    int key = 0, speed = speed_min;
                    wclear(win);
                    wbkgd(win, COLOR_PAIR(1));
                    box(win, 0, 0);
                    while ((key = wgetch(win)) != 27) {
                        change_mode(key, data, rows, columns, &speed);
                        update(data, rows, columns, speed);
                        print_field(data, rows, columns, win);
                    }
                    free_arr(data, rows);
                } else {
                    printf("There is no enough memory\n");
                }
                break;
        }
    }
    endwin();
    return 0;
}

int input_field(int **arr, int rows, int columns, int mode) {
    FILE *file = fopen("1.txt", "r");
    switch (mode) {
        case 1:
            file = fopen("1.txt", "r");
            break;
        case 2:
            file = fopen("2.txt", "r");
            break;
        case 3:
            file = fopen("3.txt", "r");
            break;
        case 4:
            file = fopen("4.txt", "r");
            break;
        case 5:
            file = fopen("5.txt", "r");
            break;
    }
    int flag = 1;
    if (file != NULL) {
        for (int i = 0; i < rows && flag; ++i) {
            for (int j = 0; j < columns && flag; ++j) {
                int val;
                if (fscanf(file, "%d", &val) == 1 && (val == 0 || val == 1)) {
                    arr[i][j] = val;
                } else {
                    flag = 0;
                }
            }
        }
    } else {
        flag = 0;
    }
    return flag;
}

void make_window(WINDOW *win) {
    noecho();
    curs_set(0);
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    wbkgd(win, COLOR_PAIR(1));
    box(win, 0, 0);
    wrefresh(win);
    halfdelay(1);
}

void menu(WINDOW *win) {
    wbkgd(win, COLOR_PAIR(2));
    mvwprintw(win, 1, 1, "Welcome to \"The Game of Life\"!");
    mvwprintw(win, 4, 1, "Here are the rules of the game:");
    mvwprintw(win, 5, 1, "1. If a live cell has fewer than two live neighbors, it ");
    mvwprintw(win, 6, 1, "dies from loneliness.");
    mvwprintw(win, 7, 1, "2. If a live cell has more than three live neighbors, it dies from ");
    mvwprintw(win, 8, 1, "overpopulation.");
    mvwprintw(win, 9, 1, "3. If a dead cell has exactly three live neighbors, it comes to life.");
    mvwprintw(win, 10, 1, "4. In all other cases, the cell remains in its current state.");
    mvwprintw(win, 13, 1, "Press Enter to Start");
    mvwprintw(win, 15, 1, "Press Esc to exit");
}

void change_mode(int mode, int **arr, int rows, int columns, int *speed) {
    switch (mode) {
        case 48:
            generate(arr, rows, columns);
            break;
        case 49:
            input_field(arr, rows, columns, 1);
            break;
        case 50:
            input_field(arr, rows, columns, 2);
            break;
        case 51:
            input_field(arr, rows, columns, 3);
            break;
        case 52:
            input_field(arr, rows, columns, 4);
            break;
        case 53:
            input_field(arr, rows, columns, 5);
            break;
        case 115:
            if (*speed < speed_max) {
                *speed += speed_step;
            }
            if (*speed > speed_max) {
                *speed = speed_max;
            }
            break;
        case 102:
            if (*speed > speed_min) {
                *speed -= speed_step;
            }
            if (*speed < speed_min) {
                *speed = speed_min;
            }
            break;
    }
}

void print_field(int **arr, int rows, int columns, WINDOW *win) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            if (arr[i][j] == 1) {
                mvwprintw(win, i - 1, j - 1, "*");
            } else {
                mvwprintw(win, i - 1, j - 1, " ");
            }
        }
    }
    mvwprintw(win, height + 2, 1,
              "Select mode: 0-Free mode 1-Stable figures 2-Guns 3-Clock 4-Pulsar 5-Glider");
    mvwprintw(win, height + 3, 1, "Press F to make it faster, S to make it slower");
    mvwprintw(win, height + 4, 1, "Press Esc to exit");
}

int neighb(int **arr, int rows, int columns, int x, int y) {
    int res = 0;
    if (0 <= x && x <= rows && 0 <= y && y <= columns) {
        if (arr[(x - 1 + height) % height][(y - 1 + width) % width] == 1) {
            res++;
        }
        if (arr[(x - 1 + height) % height][(y + width) % width] == 1) {
            res++;
        }
        if (arr[(x - 1 + height) % height][(y + 1 + width) % width] == 1) {
            res++;
        }
        if (arr[(x + height) % height][(y - 1 + width) % width] == 1) {
            res++;
        }
        if (arr[(x + height) % height][(y + 1 + width) % width] == 1) {
            res++;
        }
        if (arr[(x + 1 + height) % height][(y - 1 + width) % width] == 1) {
            res++;
        }
        if (arr[(x + 1 + height) % height][(y + width) % width] == 1) {
            res++;
        }
        if (arr[(x + 1 + height) % height][(y + 1 + width) % width] == 1) {
            res++;
        }
    } else {
        res = -1;
    }
    return res;
}

void update(int **arr, int rows, int columns, int speed) {
    int **survived = NULL;
    int **revived = NULL;
    if (place_arr(&survived, rows, columns) == 1 && place_arr(&revived, rows, columns) == 1) {
        survive(arr, rows, columns, survived);
        revive(arr, rows, columns, revived);
        merge(survived, revived, rows, columns, arr);
        free_arr(revived, rows);
        free_arr(survived, rows);
    } else {
        printf("There is no enough memory\n");
    }
    usleep(speed);
}

void survive(int **arr, int rows, int columns, int **res) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            if (arr[i][j] == 1) {
                if (neighb(arr, rows, columns, i, j) == 2 || neighb(arr, rows, columns, i, j) == 3) {
                    res[i][j] = 1;
                } else {
                    res[i][j] = 0;
                }
            }
        }
    }
}

void revive(int **arr, int rows, int columns, int **res) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            if (arr[i][j] == 0) {
                if (neighb(arr, rows, columns, i, j) == 3) {
                    res[i][j] = 1;
                } else {
                    res[i][j] = 0;
                }
            }
        }
    }
}

void merge(int **sur, int **rev, int rows, int columns, int **res) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            if (sur[i][j] == 1 || rev[i][j] == 1) {
                res[i][j] = 1;
            } else {
                res[i][j] = 0;
            }
        }
    }
}

void generate(int **arr, int rows, int columns) {
    srand(time(NULL));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            arr[i][j] = (rand() % 2) * (rand() % 2) * (rand() % 2);
        }
    }
}

int place_arr(int ***arr, int rows, int columns) {
    int flag = 0;
    (*arr) = malloc(rows * sizeof(int *));
    if (*arr != NULL) {
        flag = 1;
        int i;
        for (i = 0; i < rows && flag; ++i) {
            (*arr)[i] = calloc(columns, sizeof(int));
            if ((*arr)[i] == NULL) {
                flag = 0;
            }
        }
        if (flag == 0) {
            free_arr((*arr), i);
        }
    }
    return flag;
}

void free_arr(int **arr, int rows) {
    for (int i = 0; i < rows; ++i) {
        free(arr[i]);
    }
    free(arr);
}