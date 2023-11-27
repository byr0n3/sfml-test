#ifndef BYRONE_FLAGS
#define BYRONE_FLAGS

#include <cstdint>

namespace byrone {
	struct Flags {
		template<typename T, T value>
		inline static bool has(const T &lhs) {
			return (((uint32_t) lhs & (uint32_t) value) != 0);
		}

		template<typename T, T value>
		inline static bool lacks(T lhs) {
			return (((uint32_t) lhs & (uint32_t) value) == 0);
		}

		template<typename T, T value>
		inline static void add(T &lhs) {
			lhs = (T) ((uint32_t) lhs | (uint32_t) value);
		}

		template<typename T, T value>
		inline static void remove(T &lhs) {
			lhs = (T) ((uint32_t) lhs & ~(uint32_t) value);
		}

	};
}

#endif
