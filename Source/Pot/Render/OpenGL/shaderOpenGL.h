//
//	content	:	ShaderのOpenGLでの実装
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"

#include "./Pot/Usefull/resourceLoadList.h"
#include "./Pot/Render/shader.h"
#include "./Pot/Render/OpenGL/Platform/shaderOpenGLPlatform.h"
#include "./Pot/Render/OpenGL/Platform/inputLayoutOpenGLPlatform.h"


namespace cpot {

namespace openGL {

struct ShaderLoadDataElement {
	String<128> filePath;
};

struct ShaderLoadData {
	ShaderLoadDataElement vertexShader;
	ShaderLoadDataElement geometryShader;
	ShaderLoadDataElement fragmentShader;
	platform::InputLayout inputLayout;
};


class ShaderData : public ResourceLoadList<ShaderData, ShaderLoadData> {

};

class Shader : public ShaderBase {

public:
	void Load(const HashTableKey& aUnionName) CPOT_OR {
		mProgram.Load(ShaderData::S().Get(aUnionName).vertexShader.filePath.Get(),
			ShaderData::S().Get(aUnionName).geometryShader.filePath.Get(),
			ShaderData::S().Get(aUnionName).fragmentShader.filePath.Get());
		
		mInputLayout = ShaderData::S().Get(aUnionName).inputLayout;
	};

public:
	void Release() CPOT_OR {
		mProgram.Release();
	};

public:
	BOOL IsLoad() const CPOT_OR {
		return mProgram.IsLoaded();
	};


	//フィールド
	#pragma region Field

public:
	platform::InputLayout mInputLayout;
	platform::Program mProgram;
	
	#pragma endregion
};

}

using Shader = openGL::Shader;

}