#include <string>
#include <iostream>
#include <unistd.h>
#include "life.h"
#include <thread>

using namespace std::chrono;

int main() {
   Life life(15, 15);
   life.SetStateAlive(1,0 );
    life.SetStateAlive(2,1 );
    life.SetStateAlive(0,2 );
    life.SetStateAlive(1,2 );
    life.SetStateAlive(2,2 );
   while(true) {
       std::cout << life << std::endl;
       life.Mutate();
       std::this_thread::sleep_for(150ms);
       system("clear");
   }
}