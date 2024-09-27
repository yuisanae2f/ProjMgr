#include <ProjMgr/Screen.h>
#include <ProjMgr/Programme.h>
#include <ProjMgr/Selection.h>
#include <ProjMgr/Project.h>
#include <ProjMgr/MemMap.h>

#include <iostream>
#include <ctime>


namespace __main {
	static int AddProj();
	int Main();
	static int EditProj();
	static int DelWarn();
	static int EditProjMembers(ProjMgr::rProject& __el);

	static int EditProjMembers(ProjMgr::rProject& __el) {
		if(!ProjMgr::gMemMap.size()) {
			return 0;
		}

		const static std::vector<std::string> a{
			"- Select",
			"- Out\t"
		};

		static bool first = 1;
		int key = 0;
		while(
			(key = ProjMgr::Screen::TryGetKeyboardInput(ProjMgr::ScreenDir, ProjMgr::gMemMap.size(), 2)) == 
			ProjMgr::Screen::IS_NOT_HIT + ProjMgr::Err::LMT
		) {
			if (first) {
				ProjMgr::ScreenDir.y = ProjMgr::ScreenDir.x = 0;
				first = 0;
				__el.Mem.resize(ProjMgr::gMemMap.size(), 0);
				goto firstLbl;
			}
		}

		switch (key) {
		case ProjMgr::Screen::IS_NOT_ARROW + ProjMgr::Err::LMT: {
			if (ProjMgr::ScreenDir.y == 1) {
				first = 1;
				ProjMgr_Programme_consoleClear();
				return 0;
			}
			else {
				first = 1;
				__el.Mem[ProjMgr::ScreenDir.x] = !__el.Mem[ProjMgr::ScreenDir.x];
				return EditProjMembers(__el);
			}
		} break;

		case ProjMgr::Err::OK: firstLbl:
		{
			ProjMgr_Programme_consoleClear();
			std::cout << "Member: ["
				<< ProjMgr::gMemMap[ProjMgr::ScreenDir.x] << "]"
				<< ((__el.Mem[ProjMgr::ScreenDir.x % __el.Mem.size()]) ? "\t[Included]\n" : "\n");

			ProjMgr::Selection::Show(std::cout, ProjMgr::ScreenDir.y, "\t[selected]", a);
			break;
		}
		}

		return EditProjMembers(__el);
	};

	static int AddProj() {
		ProjMgr::rProject el;

		std::cout << "Gimme the project Name: ";
		std::getline(std::cin, el.Name);

		el.Started = std::time(0);
		el.Done = 0;

		ProjMgr_Programme_consoleClear();
		EditProjMembers(el);

		ProjMgr::gProject_Arr.push_back(el);
		ProjMgr::Programme = Main;
		return 0;
	}
	static int EditProj() {
		static bool first = 1;

		if (!ProjMgr::gProject_Arr.size()) {
			ProjMgr::Programme = Main;
			return 0;
		}

		ProjMgr::rProject& el = ProjMgr::gProject_Arr[ProjMgr::ScreenDir.x % ProjMgr::gProject_Arr.size()];
		const static std::vector<std::string> a{
			"- Name\t",
			"- Member",
			"- Cancel"
		};

		switch (ProjMgr::Screen::TryGetKeyboardInput(ProjMgr::ScreenDir, ProjMgr::gProject_Arr.size(), 3)) {
		case ProjMgr::Err::OK:
		__lbFIRST:
			ProjMgr_Programme_consoleClear();
			std::cout << "Project\n";
			ProjMgr::Project::Dump(el, ProjMgr::gMemMap, std::cout);
			std::cout << "\n";
			ProjMgr::Selection::Show(std::cout, ProjMgr::ScreenDir.y, "\t[selected]", a);
			break;

		case ProjMgr::Screen::IS_NOT_HIT + ProjMgr::Err::LMT:
			if (first) {
				first = 0;
				goto __lbFIRST;
			}

			break;
		default: {
			switch (ProjMgr::ScreenDir.y) {
			case 0:
			{
				ProjMgr_Programme_consoleClear();
				std::cout << "Gimme the another name: ";
				std::getline(std::cin, el.Name);
				
			} break;
				
			case 1:
			{
				EditProjMembers(el);
				
			} break;
			default:;
			}

			first = 1;
			ProjMgr::Programme = Main;
		}
		}

		return 0;
	}
	static int DelWarn() {
		const static std::vector<std::string> a{
			"- Yes\t",
			"- No\t"
		};

		static bool af = 1;

		if (!ProjMgr::gProject_Arr.size()) {
			ProjMgr::Programme = Main;
			return 0;
		}

		switch (ProjMgr::Screen::TryGetKeyboardInput(ProjMgr::ScreenDir, ProjMgr::gProject_Arr.size(), 2)) {
		case ProjMgr::Err::OK:
		lbaf:
			ProjMgr_Programme_consoleClear();
			std::cout << "Your Project(" << (ProjMgr::ScreenDir.x % ProjMgr::gProject_Arr.size()) << "/" << ProjMgr::gProject_Arr.size() - 1 << "), [" << (ProjMgr::gProject_Arr.begin())[(ProjMgr::ScreenDir.x % ProjMgr::gProject_Arr.size())].Name << "] will be dead.\n";
			std::cout << "Are you happy with it?\n\n";
			ProjMgr::Selection::Show(std::cout, ProjMgr::ScreenDir.y, "[selected]", a);

		case ProjMgr::Err::LMT + ProjMgr::Screen::IS_NOT_HIT:
			if (af) { af = 0; goto lbaf; }
			break;

		case ProjMgr::Err::LMT + ProjMgr::Screen::IS_NOT_ARROW:
			af = 1;
			if (ProjMgr::ScreenDir.y) goto noerase;
			ProjMgr::gProject_Arr.erase(ProjMgr::gProject_Arr.begin() + (ProjMgr::ScreenDir.x % ProjMgr::gProject_Arr.size()));
			noerase:
			ProjMgr::Programme = Main;
			return 0;
		}

		return 0;
	}
	int MemManage();
	int Main() {
		const static std::vector<std::string> a{
			"- Warp\t\t",
			"- Add Project\t",
			"- Edit Project\t",
			"- Delete Project",
			"- Member Manager",
			"- Save\t\t",
			"- Load\t\t",
			"- Close\t\t",
		};

		static bool first = 1;

		switch (ProjMgr::Screen::TryGetKeyboardInput(ProjMgr::ScreenDir, ProjMgr::gProject_Arr.size() + !ProjMgr::gProject_Arr.size(), 8)) {
		case ProjMgr::Err::OK:
		___LbWhenIsFirst:
			ProjMgr_Programme_consoleClear();
			if (ProjMgr::gProject_Arr.size()) {
				std::cout << "Project " << ProjMgr::ScreenDir.x << "/" << ProjMgr::gProject_Arr.size() - 1 << "\n";
				ProjMgr::Project::Dump(ProjMgr::gProject_Arr[ProjMgr::ScreenDir.x], ProjMgr::gMemMap, std::cout);

				std::cout << "\n";
			}
			else {
				std::cout << "No Project Found\n\n";
			}

			ProjMgr::Selection::Show(std::cout, ProjMgr::ScreenDir.y, "\t[selected]", a);
		default:
			if (first) { ProjMgr::ScreenDir.x = 0; first = 0; goto ___LbWhenIsFirst; };
			break;

		case ProjMgr::Err::LMT + ProjMgr::Screen::IS_NOT_ARROW:
			first = 1;
			ProjMgr_Programme_consoleClear();
			switch (ProjMgr::ScreenDir.y) {
			case 0:
				std::cout << "Warp Index: ";
				std::cin >> ProjMgr::ScreenDir.x; getchar();
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
				ProjMgr::Programme = MemManage;
				return 0;

			case 5: // save
			{
				ProjMgr::ScreenDir.y = 0;

				std::string path;
				std::cout << "Gimme direction to save: ";
				std::getline(std::cin, path);
				std::cout << "We are opening: " + path + ".projMgr\n";
				ProjMgr::Err::Type err = ProjMgr::FileWrite(path);
				std::cout 
				<< "File saving has done in code " << err 
				<< ".\nSomething would went wrong when the code is not zero.\n\n";
				std::cin.get();
			} return 0;

			case 6: // load
			{
				ProjMgr::ScreenDir.y = 0;

				std::string path;
				std::cout << "Gimme direction to load: ";
				std::getline(std::cin, path);
				std::cout << "We are opening: " + path + ".projMgr\n";
				ProjMgr::Err::Type err = ProjMgr::FileRead(path);
				std::cout 
				<< "File saving has done in code " << err 
				<< ".\nSomething would went wrong when the code is not zero.\n\n";
				std::cin.get();
			} return 0;
				
			default: // end & unexpected
				return 1;
			}
		}

		return 0;
	}
}


#ifndef _WIN32
#include <unistd.h>
#include <termios.h>

static struct termios orig_termios;
static void disableRawMode() {
    tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios);
}
#endif

int main() {

#ifndef _WIN32
    tcgetattr(STDIN_FILENO, &orig_termios);
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &raw);

    atexit(disableRawMode);
#endif
	#if 1
	ProjMgr::Programme = __main::Main;
	while(ProjMgr::Programme() == ProjMgr::Err::OK) {}
	#endif
	return 0;
}