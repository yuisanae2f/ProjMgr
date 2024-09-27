#include <ProjMgr/Project.h>
#include <ProjMgr/MemMap.h>
#include <fstream>
#include <stdint.h>

#define check_yielded(...) _____MACRO_ProjMgr_FileState_Switch_Check_EOF_YIELDED(__err, a, __VA_ARGS__)
#define check_strict(...) _____MACRO_ProjMgr_FileState_Switch_Check_EOF_STRICT(__err, a, __VA_ARGS__)

namespace ProjMgr {
	std::vector<rProject> gProject_Arr;

	Err::Type Project::Dump(rProject& proj, std::vector<std::string>& MemMap, std::ostream& oss) noexcept {
		oss << "Name: " << proj.Name;
		oss << "\n\nMembers:\n";

		for(size_t i = 0; i < MemMap.size() && i < proj.Mem.size(); i++)
		if(proj.Mem[i]) oss << MemMap[i] << "\n";

		if(proj.Started) {
			std::string timeString = ctime(&proj.Started);
			timeString.erase(timeString.length() - 1); 
			oss << "Beginned at: " << timeString << "\n";
		} else {
			oss << "Not yet started.\n";
			proj.Done = 0;
			return Err::OK;
		}

		if(proj.Done) {
			std::string timeString = ctime(&proj.Done);
			timeString.erase(timeString.length() - 1);
			oss << "Is done at: " << timeString << "\n";
		} else {
			oss << "Is not done yet.\n";
		}

		return Err::OK;
	}

	Err::Type Project::Init_Or_Read(std::vector<rProject>& Idx, std::ifstream& a) noexcept {
		Err::Type __err;

		if(a.is_open()) {
			union {
				uint64_t a;
				char b[sizeof(uint64_t)];
			} 
			sizeSuggested{.a = 0},
			sizeSuggested1{.a = 0};

#pragma region Check if good
			{
				uint64_t endPos;
				check_strict();
				a.seekg(0, std::ios_base::beg);

				check_strict();
				a.read(sizeSuggested.b, sizeof(uint64_t));

				check_strict();
				a.seekg(0, std::ios_base::end);

				check_yielded();
				if((endPos = a.tellg()) < sizeSuggested1.a) {
					return Err::LMT + FileState::FILE_NO_VALID;
				}

				check_yielded();
				a.seekg(sizeSuggested.a, std::ios_base::beg);

				check_strict();
				a.read(sizeSuggested1.b, sizeof(uint64_t));
				if(endPos < sizeSuggested1.a + sizeSuggested.a) {
					return Err::LMT + FileState::FILE_NO_VALID;
				}
			}
#pragma endregion

			check_strict();
			a.read(sizeSuggested.b, sizeof(uint64_t)); // from now on it's count
			#define uCount sizeSuggested
			#define uBuff sizeSuggested1

			Err::Type fsEndState = Err::OK;
			Idx.resize(uCount.a);

			// Started
			// Done
			// Name
			// Member
			for(uint64_t i = 0; i < uCount.a; i++) {
				std::cout << "Starting a loop: [" << i << "/" << uCount.a << "]\n";
				check_strict();
				a.read(reinterpret_cast<char*>(&Idx[i].Started), sizeof(time_t));

				check_strict();
				a.read(reinterpret_cast<char*>(&Idx[i].Done), sizeof(time_t));

				std::cout << "Two are done. \n";

				check_strict();
				a.read(uBuff.b, sizeof(uint64_t));
				Idx[i].Name.resize(uBuff.a, 0);

				check_strict();
				a.read(&Idx[i].Name[0], uBuff.a);

				std::cout << "Name Done: " << Idx[i].Name << "\n";
				std::cout << "Name Length: " << uBuff.a << "\n";

				check_strict();
				a.read(uBuff.b, sizeof(uint64_t));
				std::cout << "Mem size: " << uBuff.a << "\n";

				Idx[i].Mem.resize(uBuff.a << 3, 0);
				char* __Mem = (char*)(calloc(uBuff.a, 1));
				if(!__Mem) return Err::LMT + FileState::ALLOC_FAILED;
				if(fsEndState = FileState::Check(a)) {
					free(__Mem);
					goto ______InterruptedEnd;
				}

				check_strict();
				a.read(__Mem, uBuff.a);

				#define uCount uBuff
				for(size_t j = 0; j < uCount.a << 3; j++) {
					Idx[i].Mem[j] = (__Mem[j >> 3] >> (j & 7)) & 1;
					std::cout << Idx[i].Mem[j] << "\n";
				}

				std::cout << "That's a loop. \n";

				free(__Mem);
			}

			fsEndState = FileState::Check(a);
			if(fsEndState == FileState::FILE_EOF_UNEXPECTED) fsEndState = Err::OK;
			______InterruptedEnd:
			return fsEndState;
		} else return Err::LMT + FileState::FILE_OPEN_UNAVAILABLE;
	}

	Err::Type Project::Insert(const std::vector<rProject>& Idx, std::fstream& a) noexcept {
		Err::Type __err;
		if(a.is_open()) 
		{
			union {
				uint64_t a;
				char b[sizeof(uint64_t)];
			} 
			sizeSuggested{.a = 0},
			count{.a = 0};

			#pragma region Checking
			{
				check_yielded();
				a.seekg(0, std::ios_base::end);

				check_yielded();
				size_t size = a.tellg();

				check_yielded();
				a.seekg(0, std::ios_base::beg);

				check_strict();
				a.read(sizeSuggested.b, sizeof(uint64_t));

				if(size < sizeSuggested.a) {
					return Err::LMT + FileState::FILE_NO_VALID;
				} else {
					check_yielded();
					a.seekp(sizeSuggested.a + sizeof(uint64_t), std::ios_base::beg);
				}
			}
			#pragma endregion

			count.a = Idx.size();
			check_yielded();
			a.write(count.b, sizeof(uint64_t));

			union {
				uint64_t a;
				char b[sizeof(uint64_t)];
			} _insert_size = {.a = sizeof(uint64_t)};

		 	#define insert_size _insert_size.a
			// Started
			// Done
			// Name
			// Member
			for(size_t i = 0; i < count.a; i++) {
				union {
					uint64_t a;
					char b[sizeof(uint64_t)];
				} buff = { .a = 0 };
				check_yielded();
				a.write(reinterpret_cast<const char*>(&Idx[i].Started), sizeof(time_t));
				check_yielded();
				a.write(reinterpret_cast<const char*>(&Idx[i].Done), sizeof(time_t));

				buff.a = Idx[i].Name.size();

				check_yielded();
				a.write(buff.b, sizeof(uint64_t));
				check_yielded();
				a.write(Idx[i].Name.c_str(), buff.a);
				insert_size += (sizeof(time_t) << 1) + buff.a + sizeof(uint64_t);

				buff.a = Idx[i].Mem.size();
				buff.a = (buff.a >> 3) + !!(buff.a & 7);
				check_yielded();
				a.write(buff.b, sizeof(uint64_t));
				insert_size += sizeof(uint64_t);

				buff.a = Idx[i].Mem.size();

				char v = 0;
				for(size_t j = 0; j < buff.a; j++) {
					if(j && !(j & 7)) {
						check_yielded();
						a.write(&v, 1);
						v = 0; insert_size++;
					} else {
						v |= (static_cast<char>(Idx[i].Mem[j])) << (j & 7);
					}
				}

				if(buff.a & 7) {
					check_yielded();
					a.write(&v, 1);
					v = 0; insert_size++;
				}
			}

			check_yielded();
			a.seekp(sizeSuggested.a, std::ios_base::beg);
			check_yielded();
			a.write(_insert_size.b, sizeof(uint64_t));

			Err::Type fsEndState = FileState::Check(a);
			return fsEndState == FileState::FILE_EOF_UNEXPECTED ? Err::OK : fsEndState;
		}
		else return Err::LMT + FileState::FILE_OPEN_UNAVAILABLE;
	}
}