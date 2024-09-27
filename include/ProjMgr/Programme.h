#if !defined(ProjMgr_Programme_h)
#define ProjMgr_Programme_h

#include "Err.h"
#include <iostream>
#include "MemMap.h"
#include "Project.h"

namespace ProjMgr {
	/// @brief 
	/// 같은 함수函數를 반복反復하기 위하여 재귀再歸의 형태形態를 구축構築하는 것은 좋은 생각이 아니다.
	/// 
	/// 메모리의 할당割當이 끝나지 않고 반복反復되다 끝내는 덤프로 이어지기 마련이다.
	/// 
	/// 대신에 다음에 호출呼出할 함수函數를 미리 결정決定할 수 있도록 준비準備할 수 있다.
	/// 
	/// 해당 자료형資料形 정의定義는 작성作成된 함수函數의 위치位置를 나타낸다.
	typedef Err::Type(*Programme_t)();

	/// @brief 
	/// 전역全域으로 사용使用되는 다음에 호출呼出할 함수函數의 위치位置를 지정指定하는 변수이다.
	extern Programme_t Programme;

	/// @brief 
	/// 파일에서 읽어 온 정보情報를 토대土臺로 현재 정보情報를 갱신更新한다.
	/// @param ifs 
	/// 파일의 위치位置.
	/// @return 
	inline Err::Type FileRead(std::ifstream& ifs) {
		if (!ifs.is_open()) {
			return Err::LMT + FileState::FILE_OPEN_UNAVAILABLE;
		}

		Err::Type err;

		err = MemMap::Init_Or_Read(gMemMap, ifs);
		std::cout << "MemMap::Init_Or_Read completed. code: " << err << "\n";
		if (err != Err::OK) return err;

		ifs.seekg(0, std::ios_base::beg);

		err = Project::Init_Or_Read(gProject_Arr, ifs);
		std::cout << "Project::Init_Or_Read completed. code: " << err << "\n";
		if (err != Err::OK) return err;

		return Err::OK;
	}

	/// @brief 
	/// 현재現在 정보를 토대土臺로 파일의 정보情報를 갱신更新한다.
	/// @param fs 
	/// 파일의 위치位置.
	/// @return 
	inline Err::Type FileWrite(std::fstream& fs) 
	{
		if (!fs.is_open()) {
			std::cout << "[Error]: File is not open\n";
			return Err::LMT + FileState::FILE_OPEN_UNAVAILABLE;
		}

		Err::Type err = MemMap::Insert(gMemMap, fs);
		std::cout << "MemMap::Insert completed. code: " << err << "\n";
		if (err != Err::OK) return err;

		fs.seekg(0, std::ios_base::beg);
		fs.seekp(0, std::ios_base::beg);
#if 1
		err = Project::Insert(gProject_Arr, fs);
		std::cout << "Project::Insert completed. code: " << err << "\n";
		if (err != Err::OK) return err;
#endif
		return Err::OK;
	}

	/// @brief 
	/// 현재現在 정보를 토대土臺로 파일의 정보情報를 갱신更新한다.
	/// @param name
	/// 파일의 이름.
	/// 자동自動으로 뒤에 확장자擴張字 `.projMgr`를 자동自動으로 첨부添附한다.
	/// @return 
	inline Err::Type FileWrite(const std::string& name) {
		std::fstream fs; Err::Type err;
		fs.open(name + ".projMgr");
		if(fs.is_open()) {
			err = FileWrite(fs);
			fs.close();
			return err;
		} else {
			std::ofstream ofs;
			ofs.open(name + ".projMgr");
			if(!ofs.is_open()) return Err::LMT + FileState::FILE_OPEN_UNAVAILABLE;
			else ofs.close();

			fs.open(name + ".projMgr");
			err = FileWrite(fs);
			fs.close();
			return err;
		}
	}

	/// @brief 
	/// 파일에서 읽어 온 정보情報를 토대土臺로 현재 정보情報를 갱신更新한다.
	/// @param name
	/// 파일의 이름.
	/// 자동自動으로 뒤에 확장자擴張字 `.projMgr`를 자동自動으로 첨부添附한다.
	/// @return 
	inline Err::Type FileRead(const std::string& name) {
		std::ifstream ifs; Err::Type err;
		ifs.open(name + ".projMgr");
		if(ifs.is_open()) {
			err = FileRead(ifs);
			ifs.close();
			return err;
		} else return Err::LMT + FileState::FILE_OPEN_UNAVAILABLE;
	}
}

#ifdef _WIN32 
// # Windows
// 
// system을 통하여 콘솔의 출력出力 내용內容을 지우고 있다.
// ANSI 기반基盤으로 작성作成하니 출력出力이 원활圓滑히 지워지지 않는 문제問題가 있었다.
#define ProjMgr_Programme_consoleClear() system("cls")
#else 
// # LINUX
// 
// system을 통하여 콘솔의 출력出力 내용內容을 지우고 있다.
// ANSI 기반基盤으로 작성作成하니 출력出力이 원활圓滑히 지워지지 않는 문제問題가 있었다.
#define ProjMgr_Programme_consoleClear() system("clear")
#endif
#endif // !defined(ProjMgr_Programme_h)