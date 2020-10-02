#include "Player.h"

//Private functions
void Player::initVariables()
{
	this->movementSpeed = 3.f;

	this->attackCooldownMax = 1.f;
	this->attackCooldown = this->attackCooldownMax;
}

void Player::initTexture()
{
	//Load a texture from file
	if (!this->texture.loadFromFile("Textures/ship.png"))
	{
		std::cout << "Error::Player::InitTexture::Could not load texture file" << "\n";
	}
}

void Player::initSprite(float pos_x, float pos_y)
{
	//Set the texture to the sprite
	this->sprite.setTexture(this->texture);

	//resize the sprite
	this->sprite.scale(1.5f, 1.5f);
	this->sprite.setPosition(pos_x, pos_y - this->getBounds().height);
}

//Constructors and destructors
Player::Player()
{

}

Player::Player(float pos_x, float pos_y)
{
	this->initVariables();
	this->initTexture();
	this->initSprite(pos_x, pos_y);
}

Player::~Player()
{

}

const sf::Vector2f& Player::getPos() const
{
	return this->sprite.getPosition();
}

const sf::FloatRect Player::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

//Modifiers
void Player::setPosition(const sf::Vector2f pos)
{
	this->sprite.setPosition(pos);
}

void Player::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

//Public Functions
void Player::move(const float dirX, const float dirY)
{
	this->sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);
}

const bool Player::canAttack()
{
	if (this->attackCooldown >= this->attackCooldownMax)
	{
		this->attackCooldown += 0.5f;
		return true;
	}
	return false;
}

void Player::updateAttack()
{
	if (this->attackCooldown < this->attackCooldownMax)
		this->attackCooldown += 1.f;
}

void Player::update()
{
	this->updateAttack();
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}
