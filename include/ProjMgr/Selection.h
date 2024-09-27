#if !defined(ProjMgr_Selection_h)
#define ProjMgr_Selection_h

#include "Err.h"
#include "Screen.h"
#include <string>
#include <vector>

namespace ProjMgr {
	namespace Selection {
		/// @brief 
		/// @param oss 
		/// 결과結果를 표시表示할 위치位置.
		/// @param idx 
		/// 어느 축軸을 기준基準으로 한 위치位置.
		/// @param mark 
		/// 선택選擇되었음을 알리기 위해 붙이는 접미사接尾辭.
		/// @param Selections 
		/// 선택지選擇肢.
		/// @return 
		Err::Type Show(std::ostream& oss, const int idx, const char* mark, const std::vector<std::string>& Selections);
	}
}

#endif // !defined(ProjMgr_Selection_h)
