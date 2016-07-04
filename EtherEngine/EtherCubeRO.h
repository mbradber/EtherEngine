#pragma once

#include "GL/gl3w.h"
#include "vmath.h"
#include <string>

namespace Ether {
namespace Renderables {

class EtherCubeRO
{
public:
	EtherCubeRO(const std::string& texture);
	~EtherCubeRO();

	void Render(double currentTime, const vmath::mat4& mvMatrix, const vmath::mat4& projMatrix);

private:
	GLuint mVao;
	GLuint mVbo;
	GLuint mIbo;
	GLuint mTexObject;

	GLuint mProgram;
	GLuint mModelViewLoc;
	GLuint mProjLoc;
	GLuint mTexLoc;

};

}
}



