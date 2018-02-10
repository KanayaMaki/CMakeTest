#pragma once

#include "./Pot/Atom/atom.h"

#include "./Pot/Usefull/buffer.h"
#include "./Pot/File/file.h"

#include "./Pot/Render/OpenGL/Platform/bitmap.h"

#include "zlib.h"

#include "./Pot/List/vector.h"


namespace cpot {


class PngLoader {
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
	static BitmapData& Load(Buffer& aPNGData, BitmapData& aResult) {

		Vector<std::shared_ptr<Chank>> v;
		
		aPNGData.SetPosition(8);

		while (aPNGData.GetSize() != aPNGData.GetPosition()) {
			std::shared_ptr<Chank> c(new Chank);
			v.PushBack(c);
			BYTE buffer[1000000];
			aPNGData.Read(buffer, 4);
			c->length = *(s32*)buffer;
			c->length = Endian(c->length);
			aPNGData.Read(buffer, 4);
			buffer[4] = '\0';
			c->type = (const CHAR*)buffer;

			if (c->type == "IHDR") {
				aPNGData.Read(buffer, c->length);
				c->data.Add(buffer, c->length);
			}
			else if (c->type == "IDAT") {
				aPNGData.Read(buffer, c->length);
				c->data.Add(buffer, c->length);
			}
			else if (c->type == "IEND") {
				break;
			}
			else {
				aPNGData.Read(buffer, c->length);
				c->data.Add(buffer, c->length);
			}
			aPNGData.Read(buffer, 4);
		}

		s32 width = Endian(*(s32*)(&(v[0]->data[0])));
		s32 height = Endian(*(s32*)(&(v[0]->data[4])));
		s32 depth = v[0]->data[8];
		s32 colorType = v[0]->data[9];
		s32 compFormat = v[0]->data[10];
		s32 filterFormat = v[0]->data[11];
		s32 interraceFormat = v[0]->data[12];

		z_stream z;
		z.zalloc = Z_NULL;
		z.zfree = Z_NULL;
		z.opaque = Z_NULL;

		z.next_in = Z_NULL;
		z.avail_in = 0;

		s32 result = inflateInit(&z);

		Buffer pngData;
		pngData.Reserve(1024 * 1024);
		const s32 cOutBufSize = 1024 * 128;
		std::unique_ptr<BYTE> outBuf(new BYTE[cOutBufSize]);

		for (u32 i = 0; i < v.GetSize(); i++) {
			std::shared_ptr<Chank> c = v[i];

			if (c->type == "IDAT") {
				s32 status, count;
				z.next_out = (Bytef*)(&*outBuf);
				z.avail_out = cOutBufSize;
				status = Z_OK;
				z.next_in = (Bytef*)(&c->data[0]);
				z.avail_in = c->data.GetSize();

				while (status != Z_STREAM_END) {
					status = inflate(&z, Z_NO_FLUSH);
					if (status == Z_STREAM_END) break;
					if (z.avail_in == 0) {
						break;
					}
					if (status != Z_OK) {
						CPOT_ERROR("エラー");
					}
					if (z.avail_out == 0) {
						pngData.Add((&*outBuf), cOutBufSize);
						z.next_out = (Bytef*)(&*outBuf);
						z.avail_out = cOutBufSize;
					}
				}
				if ((count = cOutBufSize - z.avail_out) != 0) {
					pngData.Add((&*outBuf), count);
				}
			}
		}


		inflateEnd(&z);

		s32 pixelSize;
		switch (colorType) {
			case 0:
				pixelSize = 1 * depth / 8;
				break;
			case 2:
				pixelSize = 3 * depth / 8;
				break;
			case 4:
				pixelSize = 2 * depth / 8;
				break;
			case 6:
				pixelSize = 4 * depth / 8;
				break;
		}

		s32 widthSize = pixelSize * width + 1;

		
		for (s32 i = 0; i < height; i++) {
			s32 type = pngData[i * widthSize];
			switch (type) {
				case 0:
					break;
				case 1:
					for (s32 j = 0; j < width; j++) {
						for (s32 k = 0; k < pixelSize; k++) {
							u8 nowCol = pngData[BuildIndex(widthSize, i, j, pixelSize) + k];
							u8 leftCol;
							if (j == 0) leftCol = 0;
							else leftCol = pngData[BuildIndex(widthSize, i, j - 1, pixelSize) + k];

							pngData[BuildIndex(widthSize, i, j, pixelSize) + k] = (nowCol + leftCol) % 256;
						}
					}
					break;
				case 2:
					for (s32 j = 0; j < width; j++) {
						for (s32 k = 0; k < pixelSize; k++) {
							u8 nowCol = pngData[BuildIndex(widthSize, i, j, pixelSize) + k];
							u8 upCol;
							if (i == 0) upCol = 0;
							else upCol = pngData[BuildIndex(widthSize, i - 1, j, pixelSize) + k];

							pngData[BuildIndex(widthSize, i, j, pixelSize) + k] = (nowCol + upCol) % 256;
						}
					}
					break;
				case 3:
					for (s32 j = 0; j < width; j++) {
						for (s32 k = 0; k < pixelSize; k++) {
							u8 nowCol = pngData[BuildIndex(widthSize, i, j, pixelSize) + k];
							u8 upCol;
							if (i == 0) upCol = 0;
							else upCol = pngData[BuildIndex(widthSize, i - 1, j, pixelSize) + k];

							u8 leftCol;
							if (j == 0) leftCol = 0;
							else leftCol = pngData[BuildIndex(widthSize, i, j - 1, pixelSize) + k];

							pngData[BuildIndex(widthSize, i, j, pixelSize) + k] = (nowCol + (upCol + leftCol) / 2) % 256;
						}
					}
					break;

				case 4:
					for (s32 j = 0; j < width; j++) {
						for (s32 k = 0; k < pixelSize; k++) {
							u8 nowCol = pngData[BuildIndex(widthSize, i, j, pixelSize) + k];
							u8 upCol;
							if (i == 0) upCol = 0;
							else upCol = pngData[BuildIndex(widthSize, i - 1, j, pixelSize) + k];

							u8 leftCol;
							if (j == 0) leftCol = 0;
							else leftCol = pngData[BuildIndex(widthSize, i, j - 1, pixelSize) + k];

							u8 leftUpCol;
							if (j == 0 || i == 0) leftUpCol = 0;
							else leftUpCol = pngData[BuildIndex(widthSize, i - 1, j - 1, pixelSize) + k];

							s32 x = leftCol + upCol - leftUpCol;
							s32 a = Abs(x - leftCol);
							s32 b = Abs(x - upCol);
							s32 c = Abs(x - leftUpCol);
							s32 min = Min(a, Min(b, c));

							u8 col;
							if (min == a) col = leftCol;
							else if (min == b) col = upCol;
							else if (min == c) col = leftUpCol;

							pngData[BuildIndex(widthSize, i, j, pixelSize) + k] = (nowCol + col) % 256;
						}
					}
					break;
			}
		}
		//*/

		aResult.height = height;
		aResult.width = width;
		aResult.depth = depth;
		aResult.pixelBytes = pixelSize;
		aResult.data.Reserve(height * width * pixelSize);

		for (s32 i = height - 1; i >= 0; i--) {
			s32 start = BuildIndex(widthSize, i, 0, pixelSize);
			s32 end = BuildIndex(widthSize, i + 1, 0, pixelSize) - 1;
			aResult.data.Add((BYTE*)&(pngData[start]), end - start);
		}

		return aResult;
	}


	struct Chank {
		String<8> type;
		s32 length;
		Buffer data;
	};

	static s32 Endian(s32 e) {
		s32 a = 0;
		char* eA = (char*)&e;
		char* aA = (char*)&a;
		for (s32 i = 0; i < 4; i++) {
			aA[i] = eA[3 - i];
		}
		return a;
	}

	static s32 BuildIndex(s32 lineWidthBytes, s32 y, s32 x, s32 pixelBytes) {
		return lineWidthBytes * y + x * pixelBytes + 1;
	}

};


}
