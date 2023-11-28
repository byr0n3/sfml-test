#ifndef BYRONE_ANIMATION
#define BYRONE_ANIMATION

#include "texturesheet.h"

namespace byrone {
	class Animation {
	public:
		Animation();

		explicit Animation(float delay, int startFrame, int endFrame);

		void update(const float &deltaTime);

		[[nodiscard]] int getCurrentFrame() const;

	private:
		float delay;
		int startFrame;
		int endFrame;

		int currentFrame;
		float currentTime;
	};
}

#endif
