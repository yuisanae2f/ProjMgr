#if !defined(ProjMgr_FileState_h)
#define ProjMgr_FileState_h

#include <fstream>
#include "Err.h"

namespace ProjMgr {
    namespace FileState {
        enum e {
            // 여는 것에 실패失敗함.
            FILE_OPEN_UNAVAILABLE,
            // 유효有效하지 않음
            FILE_NO_VALID,
            // 메모리 할당割當에 실패失敗함.
            ALLOC_FAILED,
            // 파일의 끝을 읽으려 시도試圖함.
            FILE_EOF_UNEXPECTED,
            // 치명致命적인 오류誤謬가 발생함
            FILE_NO_GOOD,
            // 모종의 이유로 특정特定한 작업作業에 실패失敗함.
            FILE_OPER_FAILED,
            // 알 수 없음
            LMT, 
        };

#pragma region 해당該當하는 자료형資料形들의 부모父母 형태形態를 알지 못하므로 각 분화分化된 자료형資料形에 따라 함수函數의 정의定義를 나눈다.
        // 파일이 유효有效한가 검사檢査한다.
        // 유효성有效性 검사檢査이므로 작업作業 전에 실행實行하여야 의미意味가 있음.
        inline Err::Type Check(const std::ifstream& fs) {
            if(fs.good()) return Err::OK;
            if(fs.bad()) return Err::LMT + FILE_NO_GOOD;
            if(fs.eof()) return Err::LMT + FILE_EOF_UNEXPECTED;
            if(fs.fail()) return Err::LMT + FILE_OPER_FAILED;
            if(!fs.is_open()) return Err::LMT + FILE_OPEN_UNAVAILABLE;
            return Err::LMT + LMT;
        }

        // 파일이 유효有效한가 검사檢査한다.
        // 유효성有效性 검사檢査이므로 작업作業 전에 실행實行하여야 의미意味가 있음.
        inline Err::Type Check(const std::ofstream& fs) {
            if(fs.good()) return Err::OK;
            if(fs.bad()) return Err::LMT + FILE_NO_GOOD;
            if(fs.eof()) return Err::LMT + FILE_EOF_UNEXPECTED;
            if(fs.fail()) return Err::LMT + FILE_OPER_FAILED;
            if(!fs.is_open()) return Err::LMT + FILE_OPEN_UNAVAILABLE;
            return Err::LMT + LMT;
        }

        // 파일이 유효有效한가 검사檢査한다.
        // 유효성有效性 검사檢査이므로 작업作業 전에 실행實行하여야 의미意味가 있음.
        inline Err::Type Check(const std::fstream& fs) {
            if(fs.good()) return Err::OK;
            if(fs.bad()) return Err::LMT + FILE_NO_GOOD;
            if(fs.eof()) return Err::LMT + FILE_EOF_UNEXPECTED;
            if(fs.fail()) return Err::LMT + FILE_OPER_FAILED;
            if(!fs.is_open()) return Err::LMT + FILE_OPEN_UNAVAILABLE;
            return Err::LMT + LMT;
        }
#pragma endregion
    }
};

// 확인確認을 자동화自動化한다.
// 파일의 끝인지 확인確認하지 않는다.
#define _____MACRO_ProjMgr_FileState_Switch_Check_EOF_YIELDED(__err, fs, ...) switch(__err = FileState::Check(fs)) { default: return __err; case Err::OK: case Err::LMT + FileState::FILE_EOF_UNEXPECTED: break; }; __VA_ARGS__ 
// 확인確認을 자동화自動化한다.
// 파일의 끝인지 확인確認한다.
#define _____MACRO_ProjMgr_FileState_Switch_Check_EOF_STRICT(__err, fs, ...) switch(__err = FileState::Check(fs)) { default: return __err; case Err::OK: break; }; __VA_ARGS__

#endif