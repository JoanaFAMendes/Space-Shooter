#include "Game.h"

//Private Functions
void Game::initWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;
	this->window = new sf::RenderWindow(this->videoMode, "Space Shooter", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);
	this->window->setVerticalSyncEnabled(false);
}

void Game::initVariables()
{
	this->health = 1;
	this->insertedCredits = 50;
	this->removededCredits = 0;
	this->nPlays = 0;
	this->pause = false;
}

void Game::initTextures()
{
	this->textures["BULLET"] = new sf::Texture();
	this->textures["BULLET"]->loadFromFile("Textures/bullet.png");
	this->textures["ENEMY"] = new sf::Texture();
	this->textures["ENEMY"]->loadFromFile("Textures/enemy.png");
}

void Game::initGUI()
{
	//Load fonts
	if (this->font.loadFromFile("Fonts/PixellettersFull.ttf"))
		std::cout << "ERROR::GAME::Failed to load font" << "\n";

	//Init point text
	this->healthText.setFont(this->font);
	this->healthText.setCharacterSize(20);
	this->healthText.setFillColor(sf::Color::White);
	this->healthText.setString("Health: \n");

	this->insertedText.setFont(this->font);
	this->insertedText.setCharacterSize(20);
	this->insertedText.setFillColor(sf::Color::White);
	this->insertedText.setString("Inserted credits: \n");

	this->removedText.setFont(this->font);
	this->removedText.setCharacterSize(20);
	this->removedText.setFillColor(sf::Color::White);
	this->removedText.setString("Removed credits: \n");

	this->playsText.setFont(this->font);
	this->playsText.setCharacterSize(20);
	this->playsText.setFillColor(sf::Color::White);
	this->playsText.setString("Number plays: \n");

	this->gameOverText.setFont(this->font);
	this->gameOverText.setCharacterSize(60);
	this->gameOverText.setFillColor(sf::Color::Red);
	this->gameOverText.setString("Game Over!");
	this->gameOverText.setPosition(this->window->getSize().x / 2.f - this->gameOverText.getGlobalBounds().width / 2.f,
		this->window->getSize().y / 2.f - this->gameOverText.getGlobalBounds().height / 2.f);
}

void Game::initEnemies()
{
	this->spawnTimerMax = 50.f;
	this->spawnTimer = this->spawnTimerMax;
}

void Game::initPlayer()
{
	this->player = new Player(this->window->getSize().x / 2, this->window->getSize().y);
}

//Contructor and destroctor
Game::Game()
{
	this->initWindow();
	this->initVariables();
	this->initTextures();
	this->initGUI();
	this->initPlayer();
	this->initEnemies();
}

Game::~Game()
{
	delete this->window;
	delete this->player;

	//Delete textures
	for (auto& i : this->textures) 
	{
		delete i.second;
	}

	//Delete bullets
	for (auto* i : this->bullets) 
	{
		delete i;
	}

	//Delete enemies
	//Delete bullets
	for (auto* i : this->enemies)
	{
		delete i;
	}
}

void Game::run()
{
	while (this->window->isOpen())
	{
		this->updatePollEvents();
		if (!this->pause && this->health > 0 && this->insertedCredits > 0) {
			this->update();
		}
		this->render();
	}
}

//functions
void Game::updatePollEvents()
{
	sf::Event e;
	while (this->window->pollEvent(e))
	{
		if(e.Event::KeyPressed && e.Event::key.code == sf::Keyboard::P)
			this->pause = !this->pause;
		if (e.Event::type == sf::Event::Closed || (e.Event::KeyPressed && e.Event::key.code == sf::Keyboard::Escape))
			this->window->close();
	}
}

void Game::updateInput()
{
		//Move player
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
			this->player->move(-2.f, 0.f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
			this->player->move(2.f, 0.f);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::I)) {
			this->insertedCredits += 1;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P)) {
			this->pause = !this->pause;
		}

		
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && this->player->canAttack())
			{
				if (this->bullets.size() == 0)
				{
					this->nPlays += 1;
					this->removededCredits += 1;
					this->insertedCredits -= 1;
				}
				this->bullets.push_back(
					new Bullet(
						this->textures["BULLET"],
						this->player->getPos().x,
						this->player->getPos().y,
						0.f,
						-1.f,
						5.f
					)
				);
			}
}

void Game::updateGUI()
{
	std::stringstream ss;

	ss << "Health: " << this->health << "\n";

	this->healthText.setString(ss.str());

	ss << "Inserted credits: " << this->insertedCredits << "\n";

	this->insertedText.setString(ss.str());

	ss << "Removed credits: " << this->removededCredits << "\n";

	this->removedText.setString(ss.str());

	ss << "Number plays: " << this->nPlays << "\n";

	this->playsText.setString(ss.str());
}

void Game::updateColision()
{
	if (this->player->getBounds().left < 0.f)
	{
		this->player->setPosition(0.f, this->player->getBounds().top);
	}

	if (this->player->getBounds().left + this->player->getBounds().width > this->window->getSize().x)
	{
		this->player->setPosition(this->window->getSize().x - this->player->getBounds().width, this->player->getBounds().top);
	}
}

void Game::updateBullets()
{
	unsigned counter = 0;
	for (auto* bullet : this->bullets)
	{
		bullet->update();
		
		//Bullet top of screen
		if (bullet->getBounds().top + bullet->getBounds().height < 0.f) 
		{
			//delete bullet
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
			--counter;
			std::cout << "Bullets " << this->bullets.size() << "\n";
		}
		++counter;
	}
}

void Game::updateEnemies()
{
	this->spawnTimer += 0.5f;
	if (this->spawnTimer >= this->spawnTimerMax)
	{
		int pos_x_max = this->window->getSize().x - 40.f;
		this->enemies.push_back(new Enemy(this->textures["ENEMY"], rand() % pos_x_max, -100.f, rand() % 6 + 2));
		this->spawnTimer = 0.f;
	}

	unsigned counter = 0;
	for (auto* enemy : this->enemies)
	{
		enemy->update();

		//Enemy bottom of screen
		if (enemy->getBounds().top > this->window->getSize().y)
		{
			//delete enemy
			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);
			--counter;
		}
		else if (enemy->getBounds().intersects(this->player->getBounds()))
		{
			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);
			this->health -= 1;
			--counter;
		}
		++counter;
	}

}

void Game::updateCombat()
{
	for (int i = 0; i < this->enemies.size(); ++i)
	{
		bool enemy_deleted = false;
		for (size_t j = 0; j < this->bullets.size() && !enemy_deleted; j++)
		{
			if (this->enemies[i]->getBounds().intersects(this->bullets[j]->getBounds()))
			{
				delete this->enemies[i];
				this->enemies.erase(this->enemies.begin() + i);

				delete this->bullets[j];
				this->bullets.erase(this->bullets.begin() + j);

				std::cout << "Bullets " << this->bullets.size() << "\n";

				enemy_deleted = true;
			}
		}
	}
}

void Game::update()
{
	this->updateInput();

	this->player->update();

	this->updateColision();

	this->updateBullets();

	this->updateEnemies();

	this->updateCombat();

	this->updateGUI();
}

void Game::renderGUI()
{
	this->window->draw(this->healthText);
	this->window->draw(this->insertedText);
	this->window->draw(this->removedText);
	this->window->draw(this->playsText);
}

void Game::render()
{
	this->window->clear();

	//Draw objects
	this->player->render(*this->window);

	for (auto* bullet : this->bullets)
	{
		bullet->render(this->window);
	}

	for (auto* enemy : this->enemies)
	{
		enemy->render(this->window);
	}

	this->renderGUI();

	//render game over screen
	if (this->health <= 0 || this->insertedCredits <= 0)
		this->window->draw(this->gameOverText);

	this->window->display();
}
