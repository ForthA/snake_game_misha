#include "Game.h"

Game::Game(int width, int height, int max_length)
    : width(width),
    height(height),
    max_length(max_length)
{
    array_x.resize(max_length);
    array_y.resize(max_length);
    MoveWindow(GetConsoleWindow(), 50, 50, 800, 600, true);
    h = GetStdHandle(STD_OUTPUT_HANDLE);
    cci  = { sizeof(cci), false };
}

/**
*    Запуск игры.
*/
void Game::run() {
    srand(time(nullptr));
    SetConsoleCursorInfo(h, &cci);
    setup();
    while (!game_over) { // Игра идёт, пока не будут достигнуты какие-то конечные условия
        Sleep(sleep_time);
        if (_kbhit()) { //Если нажали по кнопке, то получаем это нажатие
            input();
        }
        logic();
    }
}
/**
*    Метод для приведения всех вспомогательных перемен к первоначальному состоянию.
*/
void Game::clear() {
    array_x.clear();
    array_y.clear();
    length = 1;
    dx = 0;
    dy = 0;
}
/**
*    Отрисовка фрукта.
*/
void Game::draw_fruit() {
    c.X = fruit_x;
    c.Y = fruit_y;
    SetConsoleCursorPosition(h, c);
    cout << fruit_char;
}
/**
*    Отрисовка границ.
*/
void Game::draw_borders() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0 || j == width - 1 || i == 0 || i == height - 1) {
                cout << border_char;
            }
            else {
                cout << empty_char;
            }
        }
        cout << endl;
    }
}

/**
*   Отрисовка головы.
*/
void Game::draw_head() {

    c.X = array_x[0];
    c.Y = array_y[0];
    SetConsoleCursorPosition(h, c);
    cout << head_char;

}
/**
*    Метод для первоначальной отрисовки клеток.
*/
void Game::draw() {

    draw_borders();
    draw_fruit();
    draw_head();

}
/**
*    Метод для настройки переменных для нового раунда игры.
*/
void Game::setup() {
    clear(); // Возвращение всех параметров игры к начальным
    game_over = false;
    array_x[0] = width/2; // Постановка змейки в середину поля
    array_y[0] = height/2;
    do { // Постановка фрукта
        fruit_x = rand() % (width - 2) + 1;
        fruit_y = rand() % (height - 2) + 1;
    } while (fruit_x != array_x[length - 1] && fruit_y != array_y[length - 1]);
    sleep_time = 200; // Время между обработками изображения (скорость)
    draw(); //Отрисовка фрукта, головы и границ
}

/**
*    Метод для обработки нажатия на стрелочки для движения.
*/
void Game::input() {

    int k = _getch();
    if (k == 0 || k == 224) {
        k = _getch();
    }
    switch (k) {
        case 80: // Нажата стрелочка вниз
            if (collision_check(0, 1)) {
                dy = 1;
                dx = 0;
            }
        break;
        case 72: // Нажата стрелочка вверх
            if (collision_check(0, -1)) {
                dy = -1; // аналогично согласно геометрической логике
                dx = 0;
            }
        break;
        case 75: // Нажата стрелочка влево
            if (collision_check(-1, 0)) {
                dy = 0;
                dx = -1;
            }
        break;
        case 77: // Нажата стрелочка вправо
            if (collision_check(1, 0)) {
                dy = 0;
                dx = 1;
            }
        break;
    }

}

/**
*    Метод для определения логики игры - проверки на достижения фрукта, конца поля и т.д.
*/

void Game::logic() {

    int X = array_x[length - 1] + dx; // Определение новых координат головы змейки
    int Y = array_y[length - 1] + dy;
    if (X == 0 || X == width - 1 || Y == 0 || Y == height - 1) // Проверка на достижение границ поля
    {
        game_over = true;
        return;
    }
    if (X == fruit_x && Y == fruit_y) {
        sleep_time -= 10; // Ускорение игры
        draw_cell(array_x[length - 1], array_y[length - 1], snake_char); // Отрисовка нового звена змейки

        length++; // Увелечения длины змейки
        if (length == max_length) { // Проверка на достижение максимальной длины змейки - если достигли, игра окончена
            game_over = true;
            return;
        }
        array_x[length - 1] = X;
        array_y[length - 1] = Y;
        draw_cell(array_x[length - 1], array_y[length - 1], head_char); // Отрисовка головы змейки

        int i;
        // Установка фрукта на новую позицию, которая не будет являться телом змейки или стеной
        do {
            fruit_x = rand() % (width - 2) + 1;
            fruit_y = rand() % (height - 2) + 1;
            i = 0;
            for (; i < length; i++)
                if (fruit_x == array_x[i] && fruit_y == array_y[i])
                    break;
        } while (i < length);

        draw_cell(fruit_x, fruit_y, fruit_char); // Отрисовка фрукта
    }
    else {
        int i = 1;
        for (; i < length; i++) // Проверка на коллизию головы змейки и тела
            if (X == array_x[i] && Y == array_y[i])
                break;
        if (i < length) {
            game_over = true;
            return;
        }
        draw_cell(array_x[0], array_y[0], empty_char); // Отрисовка пустой клетки на месте тела змейки

        if (length > 1) {
            for (int j = 1; j < length; j++) { // Отрисовка тела змейки
                draw_cell(array_x[j], array_y[j], snake_char);
            }
        }
        for (int j = 0; j < length - 1; j++) // Сдвигаем все клетки тела змейки
        {
            array_x[j] = array_x[j + 1];
            array_y[j] = array_y[j + 1];
        }

        array_x[length - 1] = X; // Устанавливаем позицию головы
        array_y[length - 1] = Y;
        draw_cell(array_x[length - 1], array_y[length - 1], head_char); // Отрисовка головы
    }

}

/**
*    Метод для проверки, может ли змейка повернуться в нужную сторону (она не может повернуться в противоположную)
*    @param dx Движение по x
*    @param dy Движение по y
*    @return True - если может, false если не может
*/

bool Game::collision_check(int dx, int dy) {
    if (length > 1) {
        if (this->dx == 1 && dx == -1 || this->dx == -1 && dx == 1)
            return false;
        if (this->dy == 1 && dy == -1 || this->dy == -1 && dy == 1)
            return false;
    }
    return true;
}
/**
*    Метод для отрисовки символа
*    @param x Координата отрисовки по x
*    @param y Координата отрисовки по y
*    @param ch Символов, который нужно отрисовать
*/
void Game::draw_cell(int x, int y, char ch) {
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(h, c);
    cout << ch;
}
