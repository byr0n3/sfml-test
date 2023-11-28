#ifndef BYRONE_ANIMATION_SET
#define BYRONE_ANIMATION_SET

#include <vector>
#include "animation.h"

namespace byrone {
	class AnimationController {
	public:
		AnimationController();

		void add(Animation animation);

		void set(const int &idx);

		void update(const float &deltaTime);

		[[nodiscard]] int getCurrentFrame() const;

	private:
		std::vector<Animation> animations;

		int currentAnimationIdx;
		int currentFrame;
		float currentTime;
	};
}

#endif
