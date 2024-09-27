#if !defined(ProjMgr_Screen_h)
#define ProjMgr_Screen_h

#include "Err.h"
#include <stdint.h>

namespace ProjMgr {
	/// @brief 화면畵面에서 선택選擇한 커서의 위치位置를 나타낸다.
	struct rScreen {
		/// @brief 가로 위치位置
		uint32_t x;
		/// @brief 세로 위치位置
		uint32_t y;

		/// @brief 
		/// 단순單純 대입代入 생성자生成者이다.
		/// @param x 
		/// @param y 
		constexpr rScreen(uint32_t x, uint32_t y)
			: x(x), y(y) {}
	};


	/// @brief 
	/// # 전역全域 변수變數이다.
	/// 
	/// 화면畵面에서 선택選擇한 커서의 위치位置를 저장貯藏한다.
	extern rScreen ScreenDir;

	namespace Screen {
		enum _Err {
			/// @brief 
			/// 위치位置가 바뀌지 않았으며, 그럴 의도가 없어 보였다.  
			/// 
			/// 해당該當 반환返還값은 무언가를 선택選擇하려 했다 추정推定한다.
			IS_NOT_ARROW,
			/// @brief 
			/// 입력入力이 존재存在하지 않았다.
			IS_NOT_HIT
		};

		/// @brief 
		/// 비정지非停止(비동기非同期) 입력入力 처리處理는 운영運營 체제體制 요청要請할 필요必要가 있다.
		/// 
		/// 그것이 비동기非同期 입력入力의 구현具現하는 방법方法이 운영체제運營體制에 따라 달라지는 원인原因이 된다.
		/// @param rs
		/// 커서의 현재現在 위치位置를 드러낸다.
		/// @param w 
		/// 너비
		/// @param h 
		/// 높이
		/// @return 
		Err::Type TryGetKeyboardInput(rScreen& rs, uint32_t w, uint32_t h) noexcept;
	}
}

#endif // !defined(ProjMgr_Screen_h)
