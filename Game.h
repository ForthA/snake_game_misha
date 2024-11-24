#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>

#ifndef GAME_H
#define GAME_H

using namespace std;

class Game {
    bool game_over;
    char border_char = '#';
    char fruit_char = '0';
    char snake_char = '*';
    char head_char = '@';
    char empty_char = ' ';
    int width;
    int height;
    int max_length;
    int dx, dy;
    int length = 1;
    vector<int> array_x;
    vector<int> array_y;
    int fruit_x, fruit_y;
    int sleep_time;
    HANDLE h; // Создание хендла потока вывода
    CONSOLE_CURSOR_INFO cci; // Создание параметров на отображение курсора
    COORD c; // Переменная для координат

public:
    Game(int width, int height, int max_length);

    void run();

private:

    void clear();

    void draw_fruit();

    void draw_borders();

    void draw_head();

    void draw();

    void setup();

    void input();

    void logic();

    bool collision_check(int dx, int dy);

    void draw_cell(int x, int y, char c);

};



#endif //GAME_H
