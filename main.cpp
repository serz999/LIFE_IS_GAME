#include <iostream>
#include "life.h"
#include "Game.h"
int main() {
    Life life(30, 30);
    life.FillRandomStates();
    Game game(&life, 10);
    game.RenderLoop();
    return 0;
}