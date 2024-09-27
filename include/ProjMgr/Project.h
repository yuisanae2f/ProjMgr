#if !defined(ProjMgr_Project_h)
#define ProjMgr_Project_h

#include <string>
#include <time.h>
#include <iostream>
#include <vector>
#include <ProjMgr/FileState.h>

#include "Err.h"

namespace ProjMgr {
	/// @brief 
	/// 프로젝트 하나의 정보情報이다.
	struct rProject {
		/// @brief 이름
		std::string Name;
		
		/// @brief 멤버.
		/// 
		/// `ProjMgr::gMemMap`을 보면 std::vector<std::string>인 걸 알 수 있는데
		/// 해당該當 멤버들 중에 어느 멤버가 프로젝트에 속屬해 있는지를 판단判斷한다.
		std::vector<bool> Mem;

		/// @brief 프로젝트가 시작始作된 시기時機.
		time_t Started;
		/// @brief 프로젝트가 끝난 시기時機.
		time_t Done;
	};

	/// @brief 
	/// 전역全域으로 사용되는 프로젝트의 정보情報를 저장貯藏하는 자료형資料形이다.
	extern std::vector<rProject> gProject_Arr;

	namespace Project {
		/// @brief 
		/// `proj`의 내용內容을 미리 맞추어 둔 형식形式에 따라 눈에 보기 좋게 출력出力한다.
		/// @param proj 
		/// 출력出力할 내용內容이 기록記錄되어 있는 레코드이다.
		/// @param MemMap 
		/// `proj`.Mem의 값이 참일 경우境遇에 표시表示할 이름을 열거列擧한 자료資料이다.
		/// @param oss 
		/// 출력할 스트림을 참조參照 형식形式으로 전달傳達한다.
		/// @return 
		Err::Type Dump(rProject& proj, std::vector<std::string>& MemMap, std::ostream& oss) noexcept;

		/// @brief 
		/// ## inline 함수函數
		/// 
		/// `proj`의 주소住所를 직접直接 참조參照하기 어려운 상황狀況을 위함이다.
		/// 
		/// `proj`의 내용內容을 미리 맞추어 둔 형식形式에 따라 눈에 보기 좋게 출력出力한다.
		/// @param proj 
		/// 출력出力할 내용內容이 기록記錄되어 있는 레코드이다.
		/// @param MemMap 
		/// `proj`.Mem의 값이 참일 경우境遇에 표시表示할 이름을 열거列擧한 자료資料이다.
		/// @param oss 
		/// 출력할 스트림을 참조參照 형식形式으로 전달傳達한다.
		/// @return 
		inline Err::Type Dump(rProject&& proj, std::vector<std::string>& MemMap, std::ostream& oss) noexcept
		{
			return Dump(proj, MemMap, oss);
		}

		/// @brief 
		/// # 반드시 ProjMgr::Project::Init_Or_Read 전前에 사용使用할 것
		///
		/// 해당 프로그램의 파일은 두 파트로 분리分離되어 있으며,
		/// 첫 파트의 길이를 알아냄으로써 두 번째 파트가 시작始作될 위치位置를 가늠한다.
		/// 
		/// 이 함수函數는 파일의 두 번째 파트를 읽는다.
		/// @param Idx 
		/// 읽은 내용內容을 담을 수 있는 Collection 형태形態의 주소住所이다.
		/// @param a 
		/// 파일의 위치位置를 나타낸다.
		/// 읽을 수 있는 형태形態이다.
		/// @return 
		Err::Type Init_Or_Read(std::vector<rProject>& Idx, std::ifstream& a) noexcept;

		/// @brief 
		/// # 반드시 ProjMgr::Project::Init_Or_Read 전前에 사용使用할 것
		///
		/// 해당 프로그램의 파일은 두 파트로 분리分離되어 있으며,
		/// 첫 파트의 길이를 알아냄으로써 두 번째 파트가 시작始作될 위치位置를 가늠한다.
		/// 
		/// 이 함수函數는 파일의 두 번째 파트를 작성作成한다.
		/// @param Idx 
		/// 파일에 작성作成하기 위한 Collection 형태形態의 주소住所이다.
		/// @param a 
		/// 파일의 위치位置를 나타낸다.
		/// 읽을 수 있는 형태形態이다.
		/// @return 
		Err::Type Insert(const std::vector<rProject>& Idx, std::fstream& a) noexcept;
	}
}

#ifndef _Win32
int kbhit();
#endif

#endif // !defined(ProjMgr_Project_h)
