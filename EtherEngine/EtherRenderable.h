#pragma once

#include "GL/gl3w.h"
#include "EtherGeometry.h"
#include <vector>
#include "vmath.h"

namespace Ether {
namespace Renderables {

class EtherRenderable
{
public:
	EtherRenderable(const std::vector<Ether::Core::EtherVert_Pos_Tex_Nml>& verts,
		const std::vector<GLushort> indices, const std::string& texPath);

	~EtherRenderable();

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
	GLuint mVertCount;
};

}
}

