#include "animation_controller.h"

byrone::AnimationController::AnimationController() : currentAnimationIdx(0), currentTime(0.0f), currentFrame(0) {
	this->animations = std::vector<byrone::Animation>();
}

void byrone::AnimationController::add(byrone::Animation animation) {
	this->animations.push_back(animation);
}

void byrone::AnimationController::set(const int &idx) {
	if (this->currentAnimationIdx == idx) {
		return;
	}

	this->currentAnimationIdx = idx;
	this->currentTime = 0.0f;
	this->currentFrame = (&this->animations[idx])->start;
}

void byrone::AnimationController::update(const float &deltaTime) {
	this->currentTime += deltaTime;

	// @todo Profile if this is performant
	byrone::Animation *animation = &this->animations[this->currentAnimationIdx];

	if (this->currentTime < animation->delay) {
		return;
	}

	if (this->currentFrame >= animation->end) {
		this->currentFrame = animation->start;
	} else {
		this->currentFrame++;
	}

	this->currentTime = 0.0f;
}

int byrone::AnimationController::getCurrentFrame() const {
	return this->currentFrame;
}
