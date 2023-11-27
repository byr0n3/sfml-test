#include "animation.h"

byrone::Animation::Animation() : textureSheet(), delay(), currentFrame(), currentTime() {
}

byrone::Animation::Animation(TextureSheet *textureSheet, float delay) : textureSheet(textureSheet), delay(delay),
                                                                        currentFrame(0), currentTime(0.0f) {
}

void byrone::Animation::update(const float &deltaTime) {
	this->currentTime += deltaTime;

	if (this->currentTime < this->delay) {
		return;
	}

	this->currentFrame++;
	this->currentTime = 0.0f;
}

int byrone::Animation::getCurrentFrame() const {
	return this->currentFrame;
}
