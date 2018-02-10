//
//	content	:	パスクラスの実装
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"

namespace cpot {

using PathString = String<128>;

class Path {
	
public:
	static PathString FromRelative(const PathString& aNowPath, const PathString& aRelativePath) {
		return GetDirectory(aNowPath) + aRelativePath;
	}

	static PathString GetDirectory(const PathString& aNowPath) {
		PathString lRes = aNowPath;

		for (u32 i = lRes.GetLength() - 1; i >= 0; i--) {
			if (lRes[i] == '/' || lRes[i] == '\\') {
				break;
			}
			lRes.Pop(1);
		}

		return lRes;
	}
	static PathString GetEx(const PathString& aNowPath) {
		PathString lPath = aNowPath;
		PathString lRes;

		for (s32 i = lPath.GetLength() - 1; i >= 0; i--) {
			if (lPath[i] == '.') {
				break;
			}
			lRes = PathString(lPath[i]) + lRes;
			lPath.Pop(1);
		}

		return lRes;
	}
	static PathString ChangeEx(const PathString& aNowPath, const String<32>& aNewEx) {
		PathString lRes = aNowPath;

		for (s32 i = lRes.GetLength() - 1; i >= 0; i--) {
			if (lRes[i] == '.') {
				break;
			}
			lRes.Pop(1);
		}

		if (lRes.GetLength() == 0) return lRes;
		return lRes + aNewEx;
	}
};


}