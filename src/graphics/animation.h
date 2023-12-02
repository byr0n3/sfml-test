#ifndef BYRONE_ANIMATION
#define BYRONE_ANIMATION

#include "texture_sheet.h"

namespace byrone {
	struct Animation {
	public:
		Animation() = default;

		explicit Animation(float delay, int startFrame, int endFrame) : delay(delay), end(endFrame), start(startFrame) {
		}

		float delay;
		int start;
		int end;
	};
}

#endif
