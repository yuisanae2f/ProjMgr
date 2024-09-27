#include <ProjMgr/Screen.h>

#if defined(_WIN32)
namespace ProjMgr {
	namespace Arrow {
		enum e {
		#if defined(WIN32)
			Key = 224,
			Up = 72,
			Down = 80,
			Right = 77,
			Left = 75
		#else
			Key = ('\033') | ((unsigned short)'[' << 8),
			Up = 'A',
			Down = 'B',
			Right = 'D',
			Left = 'C'
		#endif
		};
	}
}
#else
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>

// for unix system i guess
int kbhit() {
    struct termios oldt, newt;
    int oldf;
    char ch;
    int res;

    tcgetattr(0, &oldt);
    newt = oldt;
    newt.c_lflag &= ~ICANON; // non_blocking mode
    newt.c_lflag &= ~ECHO;   // turning off echo
    tcsetattr(0, TCSANOW, &newt);
    oldf = fcntl(0, F_GETFL, 0);
    fcntl(0, F_SETFL, oldf | O_NONBLOCK);

    res = read(0, &ch, 1);

    if(res > 0) {
        ungetc(ch, stdin);
    }

	tcsetattr(0, TCSANOW, &oldt);
    fcntl(0, F_SETFL, oldf);

    return res > 0;
}

#endif


namespace ProjMgr {
	rScreen ScreenDir( 0, 0 );

	namespace Screen {
		Err::Type TryGetKeyboardInput(rScreen& rs, uint32_t w, uint32_t h) noexcept {
#ifdef _WIN32
			if (!kbhit()) {
				return Err::LMT + IS_NOT_HIT;
			}

#if 1
			switch (getch()) {
			case ProjMgr::Arrow::Key:
#endif // 0
				switch (getch()) {
				case Arrow::Down:
					rs.y = (++rs.y);
					break;

				case Arrow::Up:
					rs.y = (--rs.y);
					break;

				case Arrow::Right:
					rs.x = (++rs.x);
					break;

				case Arrow::Left:
					rs.x = (--rs.x);
					break;

				default:
					return Err::LMT + IS_NOT_ARROW;
				}

				if (rs.x == w) rs.x = 0;
				else if (rs.x == -1) rs.x = w - 1;

				if (rs.y == h) rs.y = 0;
				else if (rs.y == -1) rs.y = h - 1;

				return Err::OK;

#if 1
			default:
				return Err::LMT + IS_NOT_ARROW;
		}
#endif // 0
#else
		if (kbhit()) {
            int ch = getchar();

            // 화살표 키는 ANSI escape sequence로 출력됨
            if (ch == 27) { // ESC 키
                getchar(); // 대괄호 '['를 읽습니다.
                ch = getchar(); // 화살표 키의 방향을 결정합니다.

                switch (ch) {
                    case 'A':
                        rs.y = (--rs.y);
                        break;
                    case 'B':
                        rs.y = (++rs.y);
                        break;
                    case 'C':
                        rs.x = (++rs.x);
                        break;
                    case 'D':
                        rs.x = (--rs.x);
                        break;
                    default:
                        return ProjMgr::Err::LMT + ProjMgr::Screen::IS_NOT_ARROW;
                }
				
				if (rs.x == w) rs.x = 0;
				else if (rs.x == -1) rs.x = w - 1;

				if (rs.y == h) rs.y = 0;
				else if (rs.y == -1) rs.y = h - 1;

				return ProjMgr::Err::OK;
            } else {
				return ProjMgr::Err::LMT + ProjMgr::Screen::IS_NOT_ARROW;
			}
        } else {
			return ProjMgr::Err::LMT + ProjMgr::Screen::IS_NOT_HIT;
		}
#endif
		}
	}
}