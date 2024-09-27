#if !defined(ProjMgr_Selection_h)
#define ProjMgr_Selection_h

#include "Err.h"
#include "Screen.h"
#include <string>
#include <vector>

namespace ProjMgr {
	namespace Selection {
		Err::Type Show(std::ostream& oss, const int idx, const char* mark, const std::vector<std::string>& Selections);
	}
}

#endif // !defined(ProjMgr_Selection_h)
