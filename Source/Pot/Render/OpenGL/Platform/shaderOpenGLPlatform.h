#pragma once

#include "./Pot/Render/OpenGL/Platform/deviceOpenGLPlatform.h"

#include "./Pot/File/file.h"


namespace cpot {

namespace openGL {

namespace platform {


inline void GetShaderInfoLog(GLuint shader) {

	GLsizei bufSize;

	/* シェーダのコンパイル時のログの長さを取得する */
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &bufSize);

	if (bufSize > 1) {
		std::unique_ptr<CHAR> infoLog(new CHAR[bufSize]);

		if (infoLog != NULL) {
			GLsizei length;

			/* シェーダのコンパイル時のログの内容を取得する */
			glGetShaderInfoLog(shader, bufSize, &length, &(*infoLog));
			CPOT_LOG((const CHAR*)&(*infoLog));
		}
	}
}
inline void GetProgramInfoLog(GLuint aProgram) {

	GLsizei lBufSize;

	/* シェーダのコンパイル時のログの長さを取得する */
	glGetProgramiv(aProgram, GL_INFO_LOG_LENGTH, &lBufSize);

	if (lBufSize > 1) {
		std::unique_ptr<CHAR> lInfoLog(new CHAR[lBufSize]);

		if (lInfoLog != NULL) {
			GLsizei lLength;

			/* シェーダのコンパイル時のログの内容を取得する */
			glGetProgramInfoLog(aProgram, lBufSize, &lLength, &(*lInfoLog));
			CPOT_LOG((const CHAR*)&(*lInfoLog));
		}
	}
}


using ShaderName = HashString<64 - sizeof(HashCode)>;

class Shader {

public:
	Shader() {
		Reset();
	}
	~Shader() {
		Release();
	}

protected:
	void Reset() {
		mGLNum = 0;
	}

public:
	void Load(const CHAR* aFileName, GLenum aShaderType) {
		if (IsLoaded()) {
			Release();
		}

		FileIn lFile;
		BOOL lRes = lFile.Open(aFileName, true);

		//もしファイルを開けなかったら
		if (!lRes) {
			CPOT_LOG("ファイル：", aFileName, "のオープンに失敗しました");
			return;
		}

		mGLNum = glCreateShader(aShaderType);

		cpot::Buffer lFileBuffer;
		lFile.Read(lFileBuffer);


		//ソースを読み込ませる
		//
		GLint lSize = lFileBuffer.GetSize();
		const GLchar* lBuffer = (const GLchar*)lFileBuffer.Get();
		glShaderSource(mGLNum, 1, &lBuffer, &lSize);


		//コンパイル
		//
		GLint tCompiled;
		glCompileShader(mGLNum);
		glGetShaderiv(mGLNum, GL_COMPILE_STATUS, &tCompiled);

		if (tCompiled == GL_FALSE) {
			//ログの表示
			CPOT_LOG("ファイル：", aFileName, "のコンパイルに失敗しました");
			GetShaderInfoLog(mGLNum);
			Release();
			return;
		}

		mShaderType = aShaderType;
		mName = aFileName;
	}
	void Release() {
		if (!IsLoaded()) {
			return;	//読み込まれていないなら、処理をしない
		}
		glDeleteShader(mGLNum);
		Reset();
	}


public:
	BOOL IsLoaded() const {
		return mGLNum != 0;
	}

	GLuint GetGLNum() const {
		return mGLNum;
	}
	const ShaderName& GetName() const {
		return mName;
	}

private:
	GLuint mGLNum;
	GLenum mShaderType;
	ShaderName mName;
};

class VertexShader : public Shader {
public:
	void Load(const CHAR* aFileName) {
		Shader::Load(aFileName, GL_VERTEX_SHADER);
	}
};

class GeometryShader : public Shader {
public:
	void Load(const CHAR* aFileName) {
		#ifndef CPOT_ON_ANDROID
		Shader::Load(aFileName, GL_GEOMETRY_SHADER);
		#endif
	}
};


class FragmentShader : public Shader {
public:
	void Load(const CHAR* aFileName) {
		Shader::Load(aFileName, GL_FRAGMENT_SHADER);
	}
};


class Program {
public:
	Program() {
		Reset();
	}
	~Program() {
		Release();
	}

private:
	void Reset() {
		mGLNum = 0;
	}

public:
	void Load(const CHAR* aVertexFileName, const CHAR* aGeometryFileName, const CHAR* aFragmentFileName) {
		VertexShader v;
		v.Load(aVertexFileName);

		GeometryShader g;
		//ジオメトリシェーダを使用する場合
		if (!StringSame(aGeometryFileName, "")) {
			g.Load(aGeometryFileName);
		}

		FragmentShader f;
		f.Load(aFragmentFileName);

		Load(&v, &g, &f);
	}
	void Load(VertexShader* aVert, GeometryShader* aGeom, FragmentShader* aFrag) {
		if (IsLoaded()) {
			Release();
		}

		mGLNum = glCreateProgram();									//プログラムオブジェクトの作成

		if (aVert) {
			glAttachShader(mGLNum, aVert->GetGLNum());							//シェーダオブジェクトのシェーダプログラムへの登録
			mVertName = aVert->GetName();
		}
		if (aGeom) {
			glAttachShader(mGLNum, aGeom->GetGLNum());							//シェーダオブジェクトのシェーダプログラムへの登録
			mGeomName = aGeom->GetName();
		}
		if (aFrag) {
			glAttachShader(mGLNum, aFrag->GetGLNum());							//シェーダオブジェクトのシェーダプログラムへの登録
			mFragName = aFrag->GetName();
		}

		glLinkProgram(mGLNum);										//シェーダプログラムのリンク
		GLint lLinked;
		glGetProgramiv(mGLNum, GL_LINK_STATUS, &lLinked);
		if (lLinked == GL_FALSE) {
			CPOT_LOG("OpenGLのProgramのリンクに失敗しました");
			GetProgramInfoLog(mGLNum);
			Release();
		}
	}
	void Release() {
		if (!IsLoaded()) {
			return;	//読み込まれていないなら、処理をしない
		}
		glDeleteProgram(mGLNum);
		Reset();
	}
	void Use() {
		glUseProgram(mGLNum);
	}


public:
	BOOL IsLoaded() const {
		return mGLNum != 0;
	}

	GLuint GetGLNum() const {
		return mGLNum;
	}

private:
	GLuint mGLNum;
	ShaderName mVertName;
	ShaderName mGeomName;
	ShaderName mFragName;
};


}

}

}
