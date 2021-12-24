#include "life.h"
#include "Game.h"

int main() {
    Life life(40, 20);
    life.FillRandomStates();
    Game game(&life, 50);
    game.RenderLoop();
    return 0;
}