#include "animation.h"

byrone::Animation::Animation() : delay(), endFrame(), startFrame(), currentFrame(), currentTime() {
}

byrone::Animation::Animation(float delay, int startFrame, int endFrame) : delay(delay), endFrame(endFrame),
																		  startFrame(startFrame),
																		  currentFrame(startFrame), currentTime(0.0f) {
}

void byrone::Animation::update(const float &deltaTime) {
	this->currentTime += deltaTime;

	if (this->currentTime < this->delay) {
		return;
	}

	if (this->currentFrame >= this->endFrame) {
		this->currentFrame = this->startFrame;
	} else {
		this->currentFrame++;
	}

	this->currentTime = 0.0f;
}

int byrone::Animation::getCurrentFrame() const {
	return this->currentFrame;
}
