#include "Game.hpp"

int main(){
    
    //init srand.
    srand(static_cast<unsigned>(time(NULL)));
    
    //init game engine
    Game game;
    
    while (game.isRunning() && !game.getEndGame()) {
        //update
        game.update();
        //render
        game.render();
    }
    
    return 0;
}
