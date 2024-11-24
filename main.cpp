#include "Game.h"

using namespace std;


int main() {
    Game game(50, 20, 20);
    do {
        game.run();
        system("cls");
        cout << "GAME OVER" << "\n";
        cout << "Press any key to restart" << "\n";
        getch();
        system("cls");
    } while (true);

    return 0;
}