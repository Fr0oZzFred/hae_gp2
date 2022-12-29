#include "Enemy.hpp"
void Enemy::im() {
}
void Enemy::update() { 
	shp->setRotation(Lib::lookAt(shp->getPosition(), player->shp->getPosition()));
	Entity::baseUpdate();
};
void Enemy::shoot() {
};