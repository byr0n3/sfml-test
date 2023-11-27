#ifndef BYRONE_ANIMATION
#define BYRONE_ANIMATION

#include "texturesheet.h"

namespace byrone {
	class Animation {
	public:
		explicit Animation(TextureSheet *textureSheet);

	private:
		TextureSheet *textureSheet;
	};
}

#endif
