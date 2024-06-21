#include "Zombie.h"

Zombie::Zombie()
{
}

Zombie::~Zombie()
{
}

void Zombie::init(float speed, glm::vec2 position)
{
	this->speed = speed;
	this->position = position;
	color.set(0, 255, 0, 255);
}

void Zombie::update(vector<string>& levelData, vector<Human*>& humans, vector<Zombie*>& zombies , Player* player)
{
	glm::vec2 direction = glm::normalize(player->getPosition() - position);
	position += direction * speed;

	// Verificar colisión con levelData
    if (collideWithLevel(levelData)) {
        if (abs(player->getPosition().x - position.x) > abs(player->getPosition().y - position.y)) {
            direction.x = (player->getPosition().x > position.x) ? speed : -speed; // Movimiento horizontal
        }
        else {
            direction.y = (player->getPosition().y > position.y) ? speed : -speed; // Movimiento vertical
        }

        position += direction * speed;
    }
}
