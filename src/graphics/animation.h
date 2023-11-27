#ifndef BYRONE_ANIMATION
#define BYRONE_ANIMATION

#include "texturesheet.h"

namespace byrone {
	class Animation {
	public:
		Animation();

		// @todo configurable max idx
		explicit Animation(TextureSheet *textureSheet, float delay);

		void update(const float &deltaTime);

		[[nodiscard]] int getCurrentFrame() const;

	private:
		TextureSheet *textureSheet;
		float delay;

		int currentFrame;
		float currentTime;
	};
}

#endif
