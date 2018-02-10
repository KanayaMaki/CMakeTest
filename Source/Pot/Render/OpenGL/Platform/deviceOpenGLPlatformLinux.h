#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/Usefull/singleton.h"
#include "./Pot/Config/config.h"
#include "./Pot/Out/out.h"

#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/freeglut.h>


namespace cpot {

namespace openGL {

namespace platform {


class Device : public Singleton<Device> {
	friend Singleton<Device>;

private:
	Device() {
		
	}

public:
	void Init() {

		//glPixelStorei(GL_UNPACK_ALIGNMENT, 4);	//RGBしかないなら1を設定するしかない。RGBAなら4アラインメントでいい。多いほうが高速
		glDepthRange(0.0, 1.0);
		glClearDepth(1.0);

		//デプスステンシルの設定
		glDisable(GL_STENCIL_TEST);	//ステンシルテストは無効

		//ビューポートの設定
		glViewport(0, 0, Config::S().GetScreenSize().x, Config::S().GetScreenSize().y);

		glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
	}
	void Final() {
		
	}

public:
	void SwapBuffer() {
		glutSwapBuffers();
	}
};


}

}

}
