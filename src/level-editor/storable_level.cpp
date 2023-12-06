#include "storable_level.h"
#include "../exceptions/load_file_exception.h"
#include <fstream>

byrone::StorableLevel::StorableLevel() = default;

byrone::StorableLevel::StorableLevel(const char *tileSetPath, const int &tileSize) : tileSetPath(tileSetPath),
																					 tileSize(tileSize),
																					 tiles() {

}

void byrone::StorableLevel::addOrReplaceTile(const int &textureId, const sf::Vector2f &position) {
	int idx = this->getTileAtPosition(position);

	if (idx != -1) {
		this->tiles[idx].setTextureIdx(textureId);
	} else {
		this->tiles.emplace_back(textureId, position);
	}
}

bool byrone::StorableLevel::removeTile(const int &index) {
	if (index > this->tiles.size() - 1) {
		return false;
	}

	this->tiles.erase(this->tiles.begin() + index);
	this->tiles.shrink_to_fit();

	return true;
}

bool byrone::StorableLevel::removeTile(const sf::Vector2f &position) {
	int index = this->getTileAtPosition(position);

	if (index == -1) {
		return false;
	}

	this->tiles.erase(this->tiles.begin() + index);
	this->tiles.shrink_to_fit();

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

	auto tileSetPathLength = (int) std::strlen(this->tileSetPath);

	stream.write((char *) &tileSetPathLength, sizeof(int));
	stream.write(this->tileSetPath, tileSetPathLength);
	stream.write((char *) &this->tileSize, sizeof(int));

	auto tileCount = (int) this->tiles.size();
	stream.write((char *) &tileCount, sizeof(int));

	for (const byrone::StorableTile &tile: this->tiles) {
		sf::Vector2f position = tile.getPosition();
		int textureId = tile.getTextureIdx();

		stream.write((char *) &textureId, sizeof(int));
		stream.write((char *) &position.x, sizeof(float));
		stream.write((char *) &position.y, sizeof(float));
	}

	stream.close();

	return stream.good();
}

byrone::StorableLevel byrone::StorableLevel::loadFromFileOrDefault(const char *path,
																   const char *defaultTileSetPath,
																   const int &defaultTileSize) {
	std::ifstream stream(path, std::ios::binary);

	if (stream.bad()) {
		return byrone::StorableLevel(defaultTileSetPath, defaultTileSize);
	}

	int tileSetPathLength;
	stream.read((char *) &tileSetPathLength, sizeof(int));

	char *tileSetPathBuffer = new char[tileSetPathLength + 1];
	stream >> tileSetPathBuffer;
	tileSetPathBuffer[tileSetPathLength] = '\0';

	int tileSize;
	stream.read((char *) &tileSize, sizeof(int));

	byrone::StorableLevel level(tileSetPathBuffer, tileSize);
	int tileCount;
	stream.read((char *) &tileCount, sizeof(int));

	for (int i = 0; i < tileCount; i++) {
		int textureId;
		float positionX;
		float positionY;

		stream.read((char *) &textureId, sizeof(int));
		stream.read((char *) &positionX, sizeof(float));
		stream.read((char *) &positionY, sizeof(float));

		level.addOrReplaceTile(textureId, sf::Vector2f(positionX, positionY));
	}

	stream.close();

	return level;
}
