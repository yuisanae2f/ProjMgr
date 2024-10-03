#if !defined(ProjMgr_MemMap_h)
#define ProjMgr_MemMap_h
#include <vector>
#include <string>
#include "Err.h"

namespace ProjMgr {
	// 전역全域에서 사용되는 구성원構成員의 이름을 저장貯藏한 변수變數이다.
	extern std::vector<std::string> gMemMap;
	namespace MemMap {
		/// @brief 
		/// # 반드시 ProjMgr::Project::Init_Or_Read 전前에 사용使用할 것
		///
		/// 해당 프로그램의 파일은 두 파트로 분리分離되어 있으며,
		/// 첫 파트의 길이를 알아냄으로써 두 번째 파트가 시작始作될 위치位置를 가늠한다.
		/// 
		/// 이 함수函數는 파일의 첫 번째 파트를 읽는다.
		/// @param Idx 
		/// 읽은 내용內容을 담을 수 있는 Collection 형태形態의 주소住所이다.
		/// @param a 
		/// 파일의 위치位置를 나타낸다.
		/// 읽을 수 있는 형태形態이다.
		/// @return 
		Err::Type Init_Or_Read(std::vector<std::string>& Idx, std::ifstream& a) noexcept;

		/// @brief 
		/// # 반드시 ProjMgr::Project::Insert 전前에 사용使用할 것
		///
		/// 해당 프로그램의 파일은 두 파트로 분리分離되어 있으며,
		/// 첫 파트의 길이를 알아냄으로써 두 번째 파트가 시작始作될 위치位置를 가늠한다.
		/// 
		/// 이 함수函數는 파일의 첫 번째 파트를 작성作成한다.
		/// @param Idx 
		/// 읽은 내용內容을 담을 수 있는 Collection 형태形態의 주소住所이다.
		/// @param a 
		/// 파일의 위치 位置를 나타낸다.
		/// 읽을 수 있는 형태形態이다.
		/// @return 
		Err::Type Insert(const std::vector<std::string>& Idx, std::fstream& a) noexcept;
	}
}

#endif