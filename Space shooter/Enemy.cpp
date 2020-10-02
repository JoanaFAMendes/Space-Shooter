#include "Enemy.h"

//Private functions
void Enemy::initVariables()
{
	this->hp = 10;
	this->hpMax = 0;
	this->damage = 1;
	this->points = 5;
	this->speed = 5.f;
}

//Constructors and destructors
Enemy::Enemy()
{
	
}

Enemy::Enemy(sf::Texture* texture, float pos_x, float pos_y, float movement_speed)
{
	this->initVariables();

	this->shape.setTexture(*texture);
	this->shape.scale(1.5f, 1.5f);

	this->shape.setPosition(pos_x, pos_y);
	this->speed = movement_speed;
}

Enemy::~Enemy()
{
}

//Accessors
const sf::FloatRect Enemy::getBounds() const
{
	return this->shape.getGlobalBounds();
}

//Public functions
void Enemy::update()
{
	this->shape.move(0.f, this->speed);
}

void Enemy::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
