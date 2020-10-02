#ifndef SPACE_SHOOTER_ENEMY
#define SPACE_SHOOTER_ENEMY

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>

class Enemy
{
private:
	sf::Sprite shape;

	float speed;
	int hp;
	int hpMax;
	int damage;
	int points;

	//Private functions
	void initVariables();

public:
	//Constructors and destructors
	Enemy();
	Enemy(sf::Texture* texture, float pos_x, float pos_y, float movement_speed);
	virtual ~Enemy();

	//Accessors
	const sf::FloatRect getBounds() const;

	//Public functions
	void update();
	void render(sf::RenderTarget* target);
};

#endif
