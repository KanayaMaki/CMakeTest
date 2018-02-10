#pragma once

#include "./Pot/Atom/atom.h"

#include "./Pot/Usefull/buffer.h"
#include "./Pot/File/file.h"

#include "./Pot/Render/OpenGL/Platform/bitmap.h"


namespace cpot {


class BmpLoader {
public:
	static BitmapData& Load(const CHAR* aFileName, BitmapData& aResult) {

		//ファイルを開く
		FileIn lFile;
		lFile.Open(aFileName, true);

		//ファイルを開けなかったら
		if (!lFile.IsOpen()) {
			return aResult;
		}

		Buffer lBuffer;
		lFile.Read(lBuffer);
		return Load(lBuffer, aResult);
	}
	static BitmapData& Load(Buffer& aBMPData, BitmapData& aResult) {

		u8 lHeader[54];
		u32 lDataPos;
		u32 lWidth, lHeight;
		u32 lLineSize;
		u32 lBytePerPixel;
		u32 lImageSize;

		aBMPData.Read(lHeader, 54);
		if (lHeader[0] != 'B' || lHeader[1] != 'M') {
			return aResult;
		}

		// バイト配列から整数を読み込む
		lDataPos = *(int*)&(lHeader[0x0A]);
		lImageSize = *(int*)&(lHeader[0x22]);
		lWidth = *(int*)&(lHeader[0x12]);
		lHeight = *(int*)&(lHeader[0x16]);

		if (aBMPData.GetSize() <= lWidth * lHeight * 4) {
			lBytePerPixel = 3;
		}
		else {
			lBytePerPixel = 4;
		}

		lLineSize = Align(lWidth * lBytePerPixel, (u32)4);
		lImageSize = lLineSize * lHeight;


		aResult.data.Create(lImageSize);
		
		
		//BMPファイルは、左下から右上にデータが格納されている
		//→縦を入れ替える必要がある
		//また、BGRやBGRAの順番でピクセルの色データが入っているので、それも変換する必要がある
		
		//RGB値を変換して書き込み
		for (s32 i = 0; i < lHeight; i++) {
			u32 lReadBase = lDataPos + i * lLineSize;	//読み込む対象ピクセルの、最初のバイトのインデックス
			u32 lWriteBase = i * lWidth * lBytePerPixel;	//書き込む対象ピクセルの、最初のバイトのインデックス
			for (u32 j = 0; j < lWidth; j++) {
				aResult.data[lWriteBase + 0] = aBMPData[lReadBase + 2]; //R
				aResult.data[lWriteBase + 1] = aBMPData[lReadBase + 1]; //G
				aResult.data[lWriteBase + 2] = aBMPData[lReadBase + 0]; //B
				lReadBase += lBytePerPixel;
				lWriteBase += lBytePerPixel;
			}
		}
		//アルファ値の書き込み
		if (lBytePerPixel == 4) {
			for (s32 i = 0; i < lHeight; i++) {
				u32 lReadBase = lDataPos + i * lLineSize;	//読み込む対象ピクセルの、最初のバイトのインデックス
				u32 lWriteBase = i * lWidth * lBytePerPixel;	//書き込む対象ピクセルの、最初のバイトのインデックス
				for (u32 j = 0; j < lWidth; j++) {
					aResult.data[lWriteBase + 3] = aBMPData[lReadBase + 3]; //A
					lReadBase += lBytePerPixel;
					lWriteBase += lBytePerPixel;
				}
			}
		}

		aResult.height = lHeight;
		aResult.width = lWidth;
		aResult.depth = 8;
		aResult.pixelBytes = lBytePerPixel;

		return aResult;
	}

};


}
