#pragma once

#include "./Pot/Render/OpenGL/Platform/deviceOpenGLPlatform.h"
#include "./Pot/File/file.h"
#include "./Pot/Usefull/path.h"

#include "./Pot/Render/OpenGL/Platform/loadBmp.h"
#include "./Pot/Render/OpenGL/Platform/loadPng.h"


namespace cpot {

namespace openGL {

namespace platform {


class Texture {

public:
	Texture() {
		Reset();
	}
	virtual ~Texture() {
		Release();
	}


protected:
	void Reset() {
		mGLNum = 0;
	}

public:
	void Release() {
		if (!IsLoaded()) {
			return;	//読み込まれていないなら、処理をしない
		}
		glDeleteTextures(1, &mGLNum);
		Reset();
	}

	virtual void Bind() = 0;


public:
	BOOL IsLoaded() const {
		return mGLNum != 0;
	}

	GLuint GetGLNum() const {
		return mGLNum;
	}

protected:
	GLuint mGLNum;
};

class Texture2D : public Texture {

public:
	void Load(u32 aWidth, u32 aHeight, void* aInitData, GLenum aInitDataFormat, GLenum aFormat, GLenum aType) {

		glGenTextures(1, &mGLNum);

		glBindTexture(GL_TEXTURE_2D, mGLNum);
		glTexImage2D(GL_TEXTURE_2D, 0, aFormat, aWidth, aHeight, 0, aInitDataFormat, aType, aInitData);

		mWidth = aWidth;
		mHeight = aHeight;
		mFormat = aFormat;
		mType = aType;
	}

	void Load(const CHAR* aFileName) {

		PathString lFileName(aFileName);

		if(lFileName.GetLength() == 0) {
			return;
		}
		if(lFileName[lFileName.GetLength() - 1] == '/') {
			return;
		}

		//ファイルから読み込む
		FileIn lFile;
		lFile.Open(lFileName.Get(), true);

		if (!lFile.IsOpen()) {
			lFileName = Path::ChangeEx(lFileName, "png");
			lFile.Open(lFileName.Get(), true);

			if (!lFile.IsOpen()) {
				lFileName = Path::ChangeEx(lFileName, "bmp");
				lFile.Open(lFileName.Get(), true);
				if (!lFile.IsOpen()) {
					return;	//ファイルを開けなかった
				}
			}
		}

		cpot::Buffer b;
		lFile.Read(b);
		
		BitmapData aBitmap;
		

		if (Path::GetEx(lFileName) == "tga") {
			return;	//tgaファイルは読み込めない
		}
		if (Path::GetEx(lFileName) == "png") {
			PngLoader::Load(b, aBitmap);
		}
		if (Path::GetEx(lFileName) == "bmp") {
			BmpLoader::Load(b, aBitmap);
		}

		if (aBitmap.pixelBytes == 3) {
			Load(aBitmap.width, aBitmap.height, &(aBitmap.data[0]), GL_RGB, GL_RGB, GL_UNSIGNED_BYTE);
		}
		else {
			Load(aBitmap.width, aBitmap.height, &(aBitmap.data[0]), GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE);
		}
	}

	void Load(u32 aWidth, u32 aHeight, GLenum aFormat, GLenum aType) {
		Load(aWidth, aHeight, nullptr, aFormat, aFormat, aType);
	}

	void GenerateMipmap() {
		glBindTexture(GL_TEXTURE_2D, mGLNum);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	void Bind() {
		glBindTexture(GL_TEXTURE_2D, mGLNum);
	}

public:
	u32 GetWidth() const {
		return mWidth;
	}
	u32 GetHeight() const {
		return mHeight;
	}
	GLenum GetType() const {
		return mType;
	}
	GLenum GetFormat() const {
		return mFormat;
	}

private:
	u32 mWidth;
	u32 mHeight;
	GLenum mType;
	GLenum mFormat;
};


}

}

}
