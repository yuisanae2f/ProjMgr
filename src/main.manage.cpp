#include <ProjMgr/Screen.h>
#include <ProjMgr/Programme.h>
#include <ProjMgr/Selection.h>
#include <ProjMgr/MemMap.h>
#include <ProjMgr/Project.h>

#include <iostream>
#include <ctime>

namespace __main {
	int Main();
	static int AddProj();
	static int EditProj();
	static int DelWarn();

	int MemManage() {
		static const std::vector<std::string> a{
			"- Warp\t\t",
			"- Add Member\t",
			"- Edit Member\t",
			"- Delete Member",
			"- Back\t\t"
		};

		static bool first = 1;

		switch (ProjMgr::Screen::TryGetKeyboardInput(ProjMgr::ScreenDir, ProjMgr::gMemMap.size() + !ProjMgr::gMemMap.size(), 5)) {
		case ProjMgr::Err::OK:
		___LbWhenIsFirst:
			ProjMgr_Programme_consoleClear();
			if (ProjMgr::gMemMap.size()) {
				std::cout << "Member " << ProjMgr::ScreenDir.x << "/" << ProjMgr::gMemMap.size() - 1 << "\n";
				std::cout << ProjMgr::gMemMap[ProjMgr::ScreenDir.x % (ProjMgr::gMemMap.size() ? ProjMgr::gMemMap.size() : 1)] << "\n\n";
			}
			else {
				std::cout << "No Member Found\n\n";
			}

			ProjMgr::Selection::Show(std::cout, ProjMgr::ScreenDir.y, "\t[selected]", a);
		default:
			if (first) { first = 0; goto ___LbWhenIsFirst; };
			break;

		case ProjMgr::Err::LMT + ProjMgr::Screen::IS_NOT_ARROW:
			first = 1;
			ProjMgr_Programme_consoleClear();
			switch (ProjMgr::ScreenDir.y) {
			case 0:
				std::cout << "Warp Index: ";
				std::cin >> ProjMgr::ScreenDir.x;
				return 0;
			case 1:
				ProjMgr::ScreenDir.y = 0;
				ProjMgr::Programme = AddProj;
				return 0;
			case 2:
				ProjMgr::ScreenDir.y = 0;
				ProjMgr::Programme = EditProj;
				return 0;

			case 3:
				ProjMgr::ScreenDir.y = 0;
				ProjMgr::Programme = DelWarn;
				return 0;

			case 4:
				ProjMgr::ScreenDir.y = 0;
				ProjMgr::Programme = Main;
				return 0;
			default:
				break;
			}
		}

		return 0;
	}

	static int AddProj() {
		ProjMgr::ScreenDir.y = 0;
		std::string a;
		std::cout << "Gimme the manager name: ";
		std::getline(std::cin, a);
		ProjMgr::gMemMap.push_back(a);
		ProjMgr::Programme = MemManage;
		return 0;
	}
	static int EditProj() {
		if (!ProjMgr::gMemMap.size()) {
			ProjMgr::Programme = MemManage;
			return 0;
		}

		std::string& el = ProjMgr::gMemMap[ProjMgr::ScreenDir.x % ProjMgr::gMemMap.size()]; 
		std::cout << "You are giving [" << el << "] a new name.\nGimme the another name: ";
		std::getline(std::cin, el);

		ProjMgr::Programme = MemManage;
		return 0;
	}

	static int DelWarn() {
		static const std::vector<std::string> a{
			"- Yes\t",
			"- No\t"
		};

		static bool af = 1;

		if (!ProjMgr::gMemMap.size()) {
			ProjMgr::Programme = MemManage;
			return 0;
		}

		switch (ProjMgr::Screen::TryGetKeyboardInput(ProjMgr::ScreenDir, ProjMgr::gMemMap.size(), 2)) {
		case ProjMgr::Err::OK:
		lbaf:
			ProjMgr_Programme_consoleClear();
			std::cout << "The name of the manager (" << (ProjMgr::ScreenDir.x % ProjMgr::gMemMap.size()) << "/" << ProjMgr::gMemMap.size() << "), [" << (ProjMgr::gMemMap.begin())[(ProjMgr::ScreenDir.x % ProjMgr::gMemMap.size())] << "] will be gone.\n";
			std::cout << "Are you happy with it?\n\n";
			ProjMgr::Selection::Show(std::cout, ProjMgr::ScreenDir.y, "[selected]", a);

		case ProjMgr::Err::LMT + ProjMgr::Screen::IS_NOT_HIT:
			if (af) { af = 0; goto lbaf; }
			break;

		case ProjMgr::Err::LMT + ProjMgr::Screen::IS_NOT_ARROW:
			if (ProjMgr::ScreenDir.y) goto NOERASE;
			af = 1;
			ProjMgr::gMemMap.erase(ProjMgr::gMemMap.begin() + (ProjMgr::ScreenDir.x % ProjMgr::gMemMap.size()));

			for(auto& k : ProjMgr::gProject_Arr)
				k.Mem.erase(k.Mem.begin() + (ProjMgr::ScreenDir.x % ProjMgr::gMemMap.size()));

			NOERASE:
			ProjMgr::Programme = MemManage;
		}

		return 0;
	}
}