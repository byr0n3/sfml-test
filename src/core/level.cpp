#include "level.h"
#include "../exceptions/load_file_exception.h"
#include <fstream>

byrone::Level::Level() = default;

byrone::Level::Level(const sf::Vector2f &playerPosition,
					 const std::vector<Tile> &tiles) : playerPosition(playerPosition), tiles(tiles) {
}

void byrone::Level::draw(sf::RenderWindow *window) {
	for (const byrone::Tile &tile: this->tiles) {
		window->draw(tile);
	}
}

sf::Vector2f byrone::Level::getPlayerPosition() const {
	return this->playerPosition;
}

std::vector<byrone::Tile> *byrone::Level::getTiles() {
	return &this->tiles;
}

byrone::Level byrone::Level::readFromFile(const char *path) {
	std::ifstream stream(path, std::ios::binary);

	if (stream.bad()) {
		throw byrone::load_file_exception(path);
	}

	int tileSetPathLength;
	stream.read((char *) &tileSetPathLength, sizeof(int));

	char *tileSetPathBuffer = new char[tileSetPathLength + 1];
	stream >> tileSetPathBuffer;
	tileSetPathBuffer[tileSetPathLength] = '\0';

	int tileSize;
	stream.read((char *) &tileSize, sizeof(int));

	// @todo no ptr
	byrone::TextureSheet *textureSheet = new byrone::TextureSheet(tileSetPathBuffer, {tileSize, tileSize});

	int tileCount;
	stream.read((char *) &tileCount, sizeof(int));

	std::vector<byrone::Tile> tiles(tileCount);

	for (int i = 0; i < tileCount; i++) {
		int textureId;
		float positionX;
		float positionY;

		stream.read((char *) &textureId, sizeof(int));
		stream.read((char *) &positionX, sizeof(float));
		stream.read((char *) &positionY, sizeof(float));

		tiles[i] = byrone::Tile(textureSheet, textureId, sf::Vector2f(positionX, positionY));
	}

	stream.close();

	return byrone::Level(sf::Vector2f(0, 0), tiles);
}
