#ifndef SPACE_SHOOTER_BULLET
#define SPACE_SHOOTER_BULLET

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>

class Bullet
{
private:
	sf::Sprite shape;

	sf::Vector2f direction;
	float movementSpeed;

public:
	//Constructors and destructors
	Bullet();
	Bullet(sf::Texture* texture, float pos_x, float pos_y, float dir_x, float dir_y, float movement_speed);
	virtual ~Bullet();

	//Accessor
	const sf::FloatRect getBounds() const;

	//Public functions
	void update();
	void render(sf::RenderTarget* target);
};

#endif

