#include<iostream>
#include<ctime>
#include<cstdlib>
#include"game.hpp"

int main(){
    srand(time(NULL));
    Game g;
    g.run();
}