#include "Game.hpp"


//Constructor && Destructor
Game::Game(){
    this->initVariables();
    this->initWindow();
    this->initEnemies();
    this->initFonts();
    this->initText();
}

Game::~Game(){
    delete this->window;
}

//Public Functions && update funcs

void Game::update(){
     
    this->pollEvents();
    
    if(!this->endGame){
        this->updateMousePos();
        this->updateEnemies();
        this->updateText();
    }
    
    //end game conditions
    if(this->health <= 0) {
        this->endGame = true;
    }
}

void Game::updateMousePos(){
    
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
    
    this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

//moving enemies and updateing.
void Game::updateEnemies(){
    
    if (this->enemies.size() < this->maxEnemies) {
        if(this->enemySpawnTimer >= this->enemySpawnTimerMax){
            this->spawnEnemy();
            this->enemySpawnTimer = 0.f;
        }
        else
            this->enemySpawnTimer += 1.f;
    }
    
    //move the enemies. and remove if reached the end.
    
    for (int i = 0; i < enemies.size(); ++i) {
        
        enemies[i].move(0.f, 5.f);
        
        if(this->enemies[i].getPosition().y > window->getSize().y){
            this->enemies.erase(this->enemies.begin() + i);
            this->health -= 10;
        }
    }
    
    //checked if clicked upon and remove.
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

        if (this->mouseHeld == false) {
            
            this->mouseHeld = true;
            bool deleted = false;
            
            for (int i = 0; i < enemies.size() && deleted == false; ++i) {
                
                if(this->enemies[i].getGlobalBounds().contains(mousePosView)){
                    
                    deleted = true;
                    
                    if(this->enemies[i].getFillColor() == sf::Color::Magenta)
                        points += 50;
                    else if(this->enemies[i].getFillColor() == sf::Color::Yellow)
                        points += 40;
                    else if(this->enemies[i].getFillColor() == sf::Color::Red)
                        points += 30;
                    else if(this->enemies[i].getFillColor() == sf::Color::Cyan)
                        points += 20;
                    else
                        points += 10;
                    
                    this->enemies.erase(this->enemies.begin() + i);
                    
                }
            }
        }
    }
    else this->mouseHeld = false;
    
}

void Game::updateText(){
    std::stringstream ss;
    
    ss << "Point: "<<this->points<<"\n"<<
    "Health:" << this->health;
    
    this->uiText.setString(ss.str());
}

//render funcs

void Game::renderText(sf::RenderTarget & target ){
    target.draw(this->uiText);
}

void Game::render(){
    this->window->clear(sf::Color(0,150,0));
    
    //draw game objects.
    this->renderEnemies(*this->window);
    
    this->renderText(*this->window );
    
    this->window->display();

}

void Game::renderEnemies(sf::RenderTarget & target){
    for(auto & e : this->enemies){
        target. draw(e);
    }
}
// -------
void Game::spawnEnemy(){
    /*
      @return void
     
      Spawm enemies and set their colors and positions.
     -sets random position. DONE
     -sets random color TODO.
     -adds enemy to the enemies vector. DONE
     -respawn if enemy touches the left border of screen. DONE EASILY
      -randomize enemy type. DONE.
     */
    
    //randomize enemy type
    int type = rand() % 5;
    
    switch (type) {
        case 0:   //hardest enemy type.
            this->enemy.setFillColor(sf::Color::Magenta);
            this->enemy.setSize(sf::Vector2f(30.f,30.f));
            break;
        case 1:
            this->enemy.setFillColor(sf::Color::Yellow);
            this->enemy.setSize(sf::Vector2f(50.f,50.f));
            break;
        case 2:
            this->enemy.setFillColor(sf::Color::Red);
            this->enemy.setSize(sf::Vector2f(70.f,70.f));
            break;
        case 3:
            this->enemy.setFillColor(sf::Color::Cyan);
            this->enemy.setSize(sf::Vector2f(90.f,90.f));
            break;
        case 4:   //easyist enemy type.
            this->enemy.setFillColor(sf::Color::Blue);
            this->enemy.setSize(sf::Vector2f(100.f,100.f));
            break;
        default:
            break;
    }
    
    this->enemy.setPosition(
             static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - (this->enemy.getScale().x) - enemy.getSize().x)),
             0.f
    );
    
    this->enemies.push_back(this->enemy);
    
}

void Game::pollEvents(){
    
    while (this->window->pollEvent(this->ev)) {
        switch (this->ev.type) {
            case sf::Event::Closed:
                this->window->close();
                break;
            case sf::Event::KeyPressed:
                if(this->ev.key.code == sf::Keyboard::Escape) this->window->close();
                break;
            default:
                break;
        }
    }
}

//ACCESORS

const bool Game::isRunning() const {
    return this->window->isOpen();
}

const bool Game::getEndGame() const {
    return this->endGame;
}

//private functions && init funcs

void Game::initWindow(){
    this->videoMode.width = 1800;
    this->videoMode.height = 1200;
    this->window = new sf::RenderWindow(this->videoMode,"SFML GAME / 1",sf::Style::Default);
    
    this->window->setFramerateLimit(60);
}

void Game::initVariables(){
    this->window = nullptr;
    
    this->points = 0;
    this->health = 100;
    this->enemySpawnTimer = 0.f;
    this->enemySpawnTimerMax = 15.f ;
    this->maxEnemies = 10;
    this->mouseHeld = false;
    this->endGame = false;
}

void Game::initEnemies(){
    this->enemy.setPosition(900, 600); //set to the center.
    this->enemy.setSize(sf::Vector2f(75.f,75.f));
    this->enemy.setFillColor(sf::Color::Cyan);
    this->enemy.setOutlineColor(sf::Color::Red);
    this->enemy.setOutlineThickness(3.f);
}

void Game::initFonts(){
    if(!this->font.loadFromFile("/Users/eren/desktop/GratelosDisplay.ttf")){
         std::cerr << "ERROR: Failed to init fonts."<< std::endl;
    }
}

void Game::initText(){
    this->uiText.setFont(this->font);
    this->uiText.setCharacterSize(60);
    this->uiText.setFillColor(sf::Color::Black);
    this->uiText.setString("NONE"); 
}
