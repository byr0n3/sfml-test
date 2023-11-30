#include "level.h"
#include "../exceptions/load_file_exception.h"
#include <fstream>
#include <string>

#define DELIMITER ' '

byrone::Level::Level() = default;

// @todo Refactor
byrone::Level::Level(const char *path, const float &windowHeight) {
	// @todo Open as binary?
	std::ifstream stream(path);

	if (!stream.is_open()) {
		throw byrone::load_file_exception(path);
	}

	std::string line;

	std::getline(stream, line);
	int spaceIdx = (int) line.find(DELIMITER);
	std::string tileSet = line.substr(0, spaceIdx);
	std::string cut = line.substr(spaceIdx + 1);
	spaceIdx = (int) cut.find(DELIMITER);
	int tileSize = std::stoi(cut.substr(0, spaceIdx));
	cut = cut.substr(spaceIdx + 1);
	spaceIdx = (int) cut.find(DELIMITER);
	int playerX = std::stoi(cut.substr(0, spaceIdx));
	cut = cut.substr(spaceIdx + 1);
	int playerY = std::stoi(cut);

	playerX *= tileSize;
	playerY = windowHeight - (playerY * tileSize);

	this->playerPosition = {(float) playerX, (float) playerY};

	this->textureSheet = new byrone::TextureSheet(("../assets/tilesets/" + tileSet).c_str(), {tileSize, tileSize});

	// @todo REFACTOR
	while (std::getline(stream, line)) {
		if (line.empty()) {
			continue;
		}

		spaceIdx = (int) line.find(DELIMITER);
		int tileIdx = std::stoi(line.substr(0, spaceIdx));

		cut = line.substr(spaceIdx + 1);
		spaceIdx = (int) cut.find(DELIMITER);
		int tileX = std::stoi(cut.substr(0, spaceIdx));
		int tileY = std::stoi(cut.substr(spaceIdx + 1));

		tileX *= tileSize;
		tileY = windowHeight - (tileY * tileSize);

		this->tiles.push_back(byrone::Tile(this->textureSheet, tileIdx, {(float) tileX, (float) tileY}));
	}

	stream.close();
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
