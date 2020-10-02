#ifndef SPACE_SHOOTER_GAME
#define SPACE_SHOOTER_GAME

#include <iostream>
#include <map>
#include <string>
#include <sstream>

#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"

//Game Engine
class Game
{
private:
	//Window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;

	//Resources
	std::map<std::string, sf::Texture*> textures;
	std::vector<Bullet*> bullets;

	//GUI
	sf::Font font;
	sf::Text healthText;
	sf::Text insertedText;
	sf::Text removedText;
	sf::Text playsText;
	sf::Text gameOverText;

	//System
	unsigned health;
	unsigned insertedCredits;
	unsigned removededCredits;
	unsigned nPlays;
	bool pause;

	//Player
	Player* player;

	//Enemies
	float spawnTimer;
	float spawnTimerMax;
	std::vector<Enemy*> enemies;

	//Private functions
	void initWindow();
	void initVariables();
	void initTextures();
	void initGUI();
	void initEnemies();
	void initPlayer();

public:
	//Constructors and destructors
	Game();
	virtual ~Game();

	//Functions
	void run();

	void updatePollEvents();
	void updateInput();
	void updateGUI();
	void updateColision();
	void updateBullets();
	void updateEnemies();
	void updateCombat();
	void update();

	void renderGUI();
	void render();
};

#endif




