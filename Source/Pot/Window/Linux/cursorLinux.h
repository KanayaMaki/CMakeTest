//
//	content	:	ウィンドウズのカーソルを制御する
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/Usefull/singleton.h"

#include <Windows.h>

namespace cpot {

namespace windows {


class Cursor : public Singleton<Cursor> {
	friend class Singleton<Cursor>;
	friend class Window;

public:
	enum CCursorState {
		cShow,
		cHide
	};
private:
	CCursorState mCursorState;

private:
	void Show() {
		while (1) {
			int times = ::ShowCursor(true);
			if (times >= 0) break;
		}
		mCursorState = cShow;
	}
	void Hide() {
		while (1) {
			int times = ::ShowCursor(false);
			if (times < 0) break;
		}
		mCursorState = cHide;
	}
	void ShowOrHide(BOOL aShow) {
		if (aShow) {
			Show();
		}
		else {
			Hide();
		}
	}

	BOOL IsShow() const {
		return mCursorState == cShow;
	}

	Vector2 GetClientPos(HWND aHwnd) const {
		POINT p;
		::GetCursorPos(&p);
		::ScreenToClient(aHwnd, &p);
		return Vector2(p.x, p.y);
	}
	void SetClientPos(HWND aHwnd, const Vector2& aClientPos) {
		POINT p;
		p.x = aClientPos.x;
		p.y = aClientPos.y;
		::ClientToScreen(aHwnd, &p);
		::SetCursorPos(p.x, p.y);
	}
};

}

}
