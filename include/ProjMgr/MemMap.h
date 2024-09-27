#if !defined(ProjMgr_MemMap_h)
#define ProjMgr_MemMap_h
#include <vector>
#include <string>
#include "Err.h"

namespace ProjMgr {
	extern std::vector<std::string> gMemMap;
	namespace MemMap {
		// write
		Err::Type Init_Or_Read(std::vector<std::string>& Idx, std::ifstream& a) noexcept;

		// read
		Err::Type Insert(const std::vector<std::string>& Idx, std::fstream& a) noexcept;
	}
}

#endif