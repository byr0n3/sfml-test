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
	int tileSize = std::stoi(line.substr(spaceIdx + 1));

	// @todo Player starting position

	this->textureSheet = new byrone::TextureSheet(("../assets/tilesets/" + tileSet).c_str(), {tileSize, tileSize});

	// @todo REFACTOR
	while (std::getline(stream, line)) {
		int firstSpaceIdx = (int) line.find(DELIMITER);
		int tileIdx = std::stoi(line.substr(0, firstSpaceIdx));

		std::string cut = line.substr(firstSpaceIdx + 1);
		int secondSpaceIdx = (int) cut.find(DELIMITER);
		float tileX = std::stof(cut.substr(0, secondSpaceIdx));
		float tileY = std::stof(cut.substr(secondSpaceIdx + 1));

		tileX *= tileSize;
		tileY *= tileSize;

		tileY = windowHeight - tileY;

		this->tiles.push_back(byrone::Tile(this->textureSheet, tileIdx, {tileX, tileY}));
	}

	stream.close();
}

void byrone::Level::draw(sf::RenderWindow *window) {
	for (const byrone::Tile &tile: this->tiles) {
		window->draw(tile);
	}
}

std::vector<byrone::Tile> *byrone::Level::getTiles() {
	return &this->tiles;
}
