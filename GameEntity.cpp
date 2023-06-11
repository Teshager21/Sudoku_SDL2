#include "GameEntity.h"

GameEntity:: GameEntity(int x, int y) {
	mPosition.at(0) = 0;
	mPosition.at(1) = 0;
}

GameEntity::GameEntity(){}
GameEntity::~GameEntity() {}

void GameEntity::SetPosition(int x, int y) {
	mPosition.at(0) = x;
	mPosition.at(1) = y;
}

std::vector<int> GameEntity:: GetPosition() { return mPosition; }