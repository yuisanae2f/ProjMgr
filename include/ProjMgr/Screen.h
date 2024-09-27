#if !defined(ProjMgr_Screen_h)
#define ProjMgr_Screen_h

#include "Err.h"
#include <stdint.h>

namespace ProjMgr {
	struct rScreen {
		uint32_t x;
		uint32_t y;

		constexpr rScreen(uint32_t x, uint32_t y)
			: x(x), y(y) {}
	};

	extern rScreen ScreenDir;

	namespace Screen {
		enum _Err {
			IS_NOT_ARROW,
			IS_NOT_HIT
		};
		Err::Type TryGetKeyboardInput(rScreen& rs, uint32_t w, uint32_t h) noexcept;
	}
}

#endif // !defined(ProjMgr_Screen_h)
