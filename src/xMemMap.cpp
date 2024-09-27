#include <ProjMgr/MemMap.h>
#include <stdint.h>
#include <ProjMgr/FileState.h>

#include <iostream>


using namespace ProjMgr;

#define switch_check_YIELDED(...) _____MACRO_ProjMgr_FileState_Switch_Check_EOF_YIELDED(__err, fs, __VA_ARGS__)
#define switch_check_STRICT(...) _____MACRO_ProjMgr_FileState_Switch_Check_EOF_STRICT(__err, fs, __VA_ARGS__)

std::vector<std::string> ProjMgr::gMemMap;
Err::Type MemMap::Init_Or_Read(std::vector<std::string>& Idx, std::ifstream& fs) noexcept
{
	Idx.clear();
	Err::Type __err;

	if (fs.is_open()) {
		{
			union {
				uint64_t b;
				char a[sizeof(uint64_t)];
			} lenSuggested = { .b = 0 };
			switch_check_STRICT(fs.seekg(0, std::ios_base::end));
			switch_check_YIELDED(size_t size = fs.tellg());
			switch_check_YIELDED(fs.seekg(0, std::ios_base::beg));
			switch_check_STRICT(fs.read(lenSuggested.a, sizeof(uint64_t)));

			if(size < lenSuggested.b) {
				return Err::LMT + FileState::FILE_NO_VALID;
			}
		}
		union {
			uint64_t b;
			char a[sizeof(uint64_t)];
		} len = { .b = 0 };
		switch_check_STRICT();
		switch_check_YIELDED(fs.seekg(8, std::ios_base::beg));
		fs.read(len.a, sizeof(uint64_t));

		for (uint64_t i = 0; i < len.b; i++) {
			union {
				uint64_t b;
				char a[sizeof(uint64_t)];
			} _len = { .b = 0 };
			switch_check_STRICT();
			fs.read(_len.a, sizeof(uint64_t));
			Idx.push_back(std::string(_len.b, '\0'));
			switch_check_STRICT();
			fs.read(&Idx.back()[0], _len.b);
		}

		switch_check_STRICT();
		fs.seekg(0, std::ios_base::end);
		Err::Type fsEndState = FileState::Check(fs);
		return fsEndState == FileState::FILE_EOF_UNEXPECTED ? Err::OK : fsEndState;
	}

	return Err::LMT + FileState::FILE_OPEN_UNAVAILABLE;
}
Err::Type MemMap::Insert(const std::vector<std::string>& Idx, std::fstream& fs) noexcept {
	Err::Type __err;
	if (fs.is_open()) {
		switch_check_YIELDED();
		fs.seekp(sizeof(uint64_t));
		union {
			uint64_t b;
			char a[sizeof(uint64_t)];
		} len = { .b = Idx.size() };

		switch_check_YIELDED();
		fs.write(len.a, sizeof(uint64_t));

		uint64_t bytesReadTotal = sizeof(uint64_t) << 1;

		for (uint64_t i = 0; i < len.b; i++) {
			union {
				uint64_t b;
				char a[sizeof(uint64_t)];
			} _len = { .b = Idx[i].length() };
			bytesReadTotal += sizeof(uint64_t) + _len.b;

			switch_check_YIELDED();
			fs.write(_len.a, sizeof(uint64_t));
			switch_check_YIELDED();
			fs.write(Idx[i].c_str(), _len.b);
		}

		switch_check_YIELDED();
		fs.seekp(0, std::ios::beg);
		len.b = bytesReadTotal;

		switch_check_YIELDED();
		fs.write(len.a, sizeof(uint64_t));
		switch_check_YIELDED();
		fs.seekp(0, std::ios_base::end);
		
		Err::Type fsEndState = FileState::Check(fs);
		return fsEndState == FileState::FILE_EOF_UNEXPECTED ? Err::OK : fsEndState;
	}

	return Err::LMT + FileState::FILE_OPEN_UNAVAILABLE;
}