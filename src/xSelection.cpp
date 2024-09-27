#include <ProjMgr/Selection.h>
#include <iostream>

namespace ProjMgr {
	namespace Selection {
		Err::Type Show(std::ostream& oss, const int idx, const char* mark, const std::vector<std::string>& Selections) {

			for (int i = 0; i < Selections.size(); i++) {
				oss << Selections[i]  << " ";
				if (idx == i) oss << mark;
				oss << '\n';
			}

			return Err::OK;
		}
	}
}