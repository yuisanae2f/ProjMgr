#if !defined(ProjMgr_Project_h)
#define ProjMgr_Project_h

#include <string>
#include <time.h>
#include <iostream>
#include <vector>
#include <ProjMgr/FileState.h>

#include "Err.h"

namespace ProjMgr {
	struct rProject {
		std::string Name;
		std::vector<bool> Mem;
		time_t Started;
		time_t Done;
	};

	extern std::vector<rProject> gProject_Arr;

	namespace Project {
		Err::Type Dump(rProject& proj, std::vector<std::string>& MemMap, std::ostream& oss) noexcept;
		inline Err::Type Dump(rProject&& proj, std::vector<std::string>& MemMap, std::ostream& oss) noexcept
		{
			return Dump(proj, MemMap, oss);
		}

		Err::Type Init_Or_Read(std::vector<rProject>& Idx, std::ifstream& a) noexcept;
		Err::Type Insert(const std::vector<rProject>& Idx, std::fstream& a) noexcept;
	}
}

#ifndef _Win32
int kbhit();
#endif

#endif // !defined(ProjMgr_Project_h)
