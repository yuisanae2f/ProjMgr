#if !defined(ProjMgr_Err_h)
#define ProjMgr_Err_h

namespace ProjMgr {
	namespace Err {
		// 작업作業이 성공成功적으로 완료完了되었는가를 확인確認하기 위함.
		// 결과結果가 e::OK가 아닐 경우 문제가 생김을 확인할 수 있다.
		enum e {
			// 성공成功.
			OK,
			// 실패失敗. 
			LMT
		};

		// 예외例外 상황狀況을 표현表現하기 위한 자료형資料形.
		using Type = int;
	}
}

#endif // !defined(ProjMgr_Err_h)
