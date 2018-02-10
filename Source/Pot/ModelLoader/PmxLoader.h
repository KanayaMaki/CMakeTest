#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/List/vector.h"

#include "./Pot/Usefull/buffer.h"

#include "./Pot/ModelLoader/PmdData.h"
#include "./Pot/ModelLoader/PmxData.h"


namespace cpot {

class PmxLoader {

	//ロード
	#pragma region Load

public:
	BOOL Load(const CHAR* aFileName);

private:
	BOOL Load(Buffer& aData);

	#pragma endregion


	//リリース
	#pragma region Release

public:
	void Release();
	
	#pragma endregion


	//取得
	#pragma region Getter

public:
	BOOL IsLoaded() const;

	PmxData& Get() {
		return mData;
	}

	#pragma endregion

	
	//ロード時に使用する
	#pragma region OnLoad

private:
	BOOL IsUtf8() const {
		return mData.header.byteSizes[0] == 1;
	}
	BOOL IsUtf16() const {
		return mData.header.byteSizes[0] == 0;
	}

	s32 AddUvNum() const {
		return mData.header.byteSizes[1];
	}
	s32 VertexIndexByteNum() const {
		return mData.header.byteSizes[2];
	}
	s32 TextureIndexByteNum() const {
		return mData.header.byteSizes[3];
	}
	s32 MaterialIndexByteNum() const {
		return mData.header.byteSizes[4];
	}
	s32 BoneIndexByteNum() const {
		return mData.header.byteSizes[5];
	}
	s32 MorphIndexByteNum() const {
		return mData.header.byteSizes[6];
	}
	s32 PhysicsIndexByteNum() const {
		return mData.header.byteSizes[7];
	}

	s32 WeightDataByteNum(s32 type) const {
		switch (type) {
			case 0:
				return BoneIndexByteNum();

			case 1:
				return BoneIndexByteNum() * 2 + sizeof(f32) * 1;

			case 2:
				return BoneIndexByteNum() * 4 + sizeof(f32) * 4;

			case 3:
				return BoneIndexByteNum() * 2 + sizeof(f32) * 1 + sizeof(f32) * 3 * 3;
		}
	}

	s32 MorphTypeByteNum(u8 aMorphType) const {
		switch (aMorphType) {
			case 0:
				return MorphIndexByteNum() + sizeof(f32);
			case 1:
				return VertexIndexByteNum() + sizeof(f32) * 3;
			case 2:
				return BoneIndexByteNum() + sizeof(f32) * 3 + sizeof(f32) * 4;
			case 3:
				return VertexIndexByteNum() + sizeof(f32) * 4;
			case 4:
			case 5:
			case 6:
			case 7:
				return 0;
			case 8:
				return MaterialIndexByteNum() + sizeof(u8) + sizeof(f32) * 4 +
					sizeof(f32) * 3 + sizeof(f32) + sizeof(f32) * 3 + sizeof(f32) * 4 +
					sizeof(f32) + sizeof(f32) * 4 + sizeof(f32) * 4 + sizeof(f32) * 4;
		}
	}

	void ReadTextBuf(Buffer& aData, PmxData::TextBuf& aTextBuf);

	s32 ReadChangeValue(Buffer& aData, s32 byteNum);


	#pragma endregion


private:
	PmxData mData;
};

}
