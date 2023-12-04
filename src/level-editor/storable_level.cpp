#include "storable_level.h"
#include "../exceptions/load_file_exception.h"
#include <fstream>
#include <iostream>

byrone::StorableLevel::StorableLevel() : tileSize(0) {
}

byrone::StorableLevel::StorableLevel(const char *tileSetPath, const int &tileSize) : tileSetPath(tileSetPath),
																					 tileSize(tileSize),
																					 tiles() {

}

void byrone::StorableLevel::addOrReplaceTile(const int &textureId, const sf::Vector2f &position) {
	int idx = this->getTileAtPosition(position);

	if (idx != -1) {
		if (this->tiles[idx].getTextureIdx() != textureId) {
			this->tiles[idx] = byrone::StorableTile(textureId, position);
		}
	} else {
		this->tiles.emplace_back(textureId, position);
	}
}

bool byrone::StorableLevel::removeTile(const int &index) {
	if (index > this->tiles.size() - 1) {
		return false;
	}

	this->tiles.erase(this->tiles.begin() + index);
	// @todo Deconstruct old value & shrink to fit?
	return true;
}

bool byrone::StorableLevel::removeTile(const sf::Vector2f &position) {
	int index = this->getTileAtPosition(position);

	if (index == -1) {
		return false;
	}

	this->tiles.erase(this->tiles.begin() + index);
	// @todo Deconstruct old value & shrink to fit?
	return true;
}

int byrone::StorableLevel::getTileAtPosition(const sf::Vector2f &position) {
	for (int i = 0; i < this->tiles.size(); i++) {
		if (this->tiles[i].getPosition() == position) {
			return i;
		}
	}

	return -1;
}

const char *byrone::StorableLevel::getTileSetPath() const {
	return this->tileSetPath;
}

int byrone::StorableLevel::getTileSize() const {
	return this->tileSize;
}

std::vector<byrone::StorableTile> *byrone::StorableLevel::getTiles() {
	return &this->tiles;
}

bool byrone::StorableLevel::write(const char *path) {
	std::ofstream stream(path, std::ios::binary);

	if (stream.bad()) {
		return false;
	}

	auto tileSetPathLength = std::strlen(this->tileSetPath);

	stream << tileSetPathLength << this->tileSetPath;
	stream << this->tileSize;

	stream << this->tiles.size();

	for (const byrone::StorableTile &tile: this->tiles) {
		sf::Vector2f position = tile.getPosition();
		stream << tile.getTextureIdx() << position.x << position.y;
	}

	stream.close();

	return stream.good();
}

byrone::StorableLevel byrone::StorableLevel::readFromFile(const char *path) {
	std::ifstream stream(path, std::ios::binary);

	if (stream.bad()) {
		throw byrone::load_file_exception(path);
	}

	int tileSetPathLength;
	stream >> tileSetPathLength;

	char *tileSetPathBuffer = new char[tileSetPathLength + 1];
	stream >> tileSetPathBuffer;
	tileSetPathBuffer[tileSetPathLength] = '\0';

	int tileSize;
	stream >> tileSize;

	byrone::StorableLevel level(tileSetPathBuffer, tileSize);
	int tileCount;
	stream >> tileCount;

	for (int i = 0; i < tileCount; i++) {
		int textureId;
		float positionX;
		float positionY;

		stream >> textureId >> positionX >> positionY;

		level.addOrReplaceTile(textureId, sf::Vector2f(positionX, positionY));
	}

	return level;
}
