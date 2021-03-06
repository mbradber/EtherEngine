#pragma once

#include "GL/gl3w.h"
#include "EtherGeometry.h"
#include <vector>
#include "EtherMath.h"

namespace Ether {
namespace Renderables {

class EtherRenderable
{
public:
	EtherRenderable(const std::vector<Ether::Core::EtherVert_Pos_Tex_Nml>& verts,
		const std::vector<GLushort> indices, const std::string& texPath);

	~EtherRenderable();

	void Render(double currentTime, const glm::mat4& modelMatrix, const glm::mat4& viewMatrix, const glm::mat4& projMatrix);

private:
	GLuint mVao;
	GLuint mVbo;
	GLuint mIbo;
	GLuint mTexObject;

	GLuint mProgram;
	GLuint mModelMatrixLoc;
	GLuint mViewMatrixLoc;
	GLuint mProjMatrixLoc;
	GLuint mTexLoc;
	GLuint mVertCount;
};

}
}

