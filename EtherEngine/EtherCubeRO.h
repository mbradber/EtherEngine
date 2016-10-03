#pragma once

#include "GL/gl3w.h"
#include <string>
#include "EtherMath.h"

namespace Ether {
namespace Renderables {

class EtherCubeRO
{
public:
	EtherCubeRO(const std::string& texture);
	~EtherCubeRO();

	void Render(double currentTime, const glm::mat4& mvMatrix, const glm::mat4& projMatrix);

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



