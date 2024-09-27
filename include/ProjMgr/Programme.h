#if !defined(ProjMgr_Programme_h)
#define ProjMgr_Programme_h

#include "Err.h"
#include <iostream>
#include "MemMap.h"
#include "Project.h"

namespace ProjMgr {
	typedef Err::Type(*Programme_t)();

	extern Programme_t Programme;

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

	inline Err::Type FileWrite(std::fstream& fs) {
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
#define ProjMgr_Programme_consoleClear() system("cls")
#else 
#define ProjMgr_Programme_consoleClear() system("clear")
#endif
#endif // !defined(ProjMgr_Programme_h)