#pragma once

#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>
 
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"

/*  Class that acts the game engine
     Wrapper class
 */

class Game{
private:
    
    //Variables
    //Window
    sf::RenderWindow * window;
    sf::Event ev;
    sf::VideoMode videoMode;
    
    //Mouse Positions
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;
    
    
    //resources
    sf::Font font;
    
    //text
    sf::Text uiText;
    
    
    //Game Logic
    float enemySpawnTimer;
    float enemySpawnTimerMax;
    int maxEnemies;
    int health;
    unsigned int points;
    bool mouseHeld;
    bool endGame;
    
    
    //GameObjects
    std::vector<sf::RectangleShape> enemies;
    sf::RectangleShape enemy;
    
    //private functions
    void initVariables();
    void initWindow();
    void initEnemies();
    void initFonts();
    void initText();
public:
    // Constructors && Destractors
    Game();
    virtual ~Game();
    
    //Accesors
    const bool isRunning() const;
    const bool getEndGame() const;
    
    //public functions
    void spawnEnemy();
    
    void pollEvents();
    
    void updateEnemies();
    void updateText();
    void updateMousePos();
    void update();
    
    void renderEnemies(sf::RenderTarget & target);
    void renderText(sf::RenderTarget & target);
    void render();
};

