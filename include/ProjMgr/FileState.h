#if !defined(ProjMgr_FileState_h)
#define ProjMgr_FileState_h

#include <fstream>
#include "Err.h"

namespace ProjMgr {
    namespace FileState {
        enum e {
            FILE_OPEN_UNAVAILABLE,
            FILE_NO_VALID,
            ALLOC_FAILED,
            FILE_EOF_UNEXPECTED,
            FILE_NO_GOOD,
            FILE_OPER_FAILED,
            LMT, // I don't know what the hell is going on
        };

        inline Err::Type Check(const std::ifstream& fs) {
            if(fs.good()) return Err::OK;
            if(fs.bad()) return Err::LMT + FILE_NO_GOOD;
            if(fs.eof()) return Err::LMT + FILE_EOF_UNEXPECTED;
            if(fs.fail()) return Err::LMT + FILE_OPER_FAILED;
            if(!fs.is_open()) return Err::LMT + FILE_OPEN_UNAVAILABLE;
            return Err::LMT + LMT;
        }

        inline Err::Type Check(const std::ofstream& fs) {
            if(fs.good()) return Err::OK;
            if(fs.bad()) return Err::LMT + FILE_NO_GOOD;
            if(fs.eof()) return Err::LMT + FILE_EOF_UNEXPECTED;
            if(fs.fail()) return Err::LMT + FILE_OPER_FAILED;
            if(!fs.is_open()) return Err::LMT + FILE_OPEN_UNAVAILABLE;
            return Err::LMT + LMT;
        }

        inline Err::Type Check(const std::fstream& fs) {
            if(fs.good()) return Err::OK;
            if(fs.bad()) return Err::LMT + FILE_NO_GOOD;
            if(fs.eof()) return Err::LMT + FILE_EOF_UNEXPECTED;
            if(fs.fail()) return Err::LMT + FILE_OPER_FAILED;
            if(!fs.is_open()) return Err::LMT + FILE_OPEN_UNAVAILABLE;
            return Err::LMT + LMT;
        }
    }
};

#define _____MACRO_ProjMgr_FileState_Switch_Check_EOF_YIELDED(__err, fs, ...) switch(__err = FileState::Check(fs)) { default: return __err; case Err::OK: case Err::LMT + FileState::FILE_EOF_UNEXPECTED: break; }; __VA_ARGS__ 
#define _____MACRO_ProjMgr_FileState_Switch_Check_EOF_STRICT(__err, fs, ...) switch(__err = FileState::Check(fs)) { default: return __err; case Err::OK: break; }; __VA_ARGS__

#endif