#include "EtherPlatform.h"
#include "EtherRenderable.h"
#include "EtherApp.h"
#include "EtherLog.h"
#include "sb7ktx.h"

namespace Ether {
namespace Renderables {

EtherRenderable::EtherRenderable(const std::vector<Ether::Core::EtherVert_Pos_Tex_Nml>& verts,
	const std::vector<GLushort> indices, const std::string& texPath): mVertCount(indices.size()) { 
	// build shader object & grab uniform locs
	mProgram = glCreateProgram();

	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	Ether::Core::EtherApp::CompileShader(fs, "texture_map_basic_fs.glsl");

	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	Ether::Core::EtherApp::CompileShader(vs, "texture_map_basic_vs.glsl");

	glAttachShader(mProgram, fs);
	glAttachShader(mProgram, vs);

	glLinkProgram(mProgram);

	glDeleteShader(fs);
	glDeleteShader(vs);

	Ether::Core::EtherApp::CheckLinkStatus(mProgram);

	mModelViewLoc = glGetUniformLocation(mProgram, "mv_matrix");
	mProjLoc = glGetUniformLocation(mProgram, "proj_matrix");
	mTexLoc = glGetUniformLocation(mProgram, "tex_object");

	// build up vertex data
	glGenVertexArrays(1, &mVao);
	glBindVertexArray(mVao);

	// load VBO
	glGenBuffers(1, &mVbo);
	glBindBuffer(GL_ARRAY_BUFFER, mVbo);
	glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(EtherVertPTN), verts.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(EtherVertPTN), NULL);
	glEnableVertexAttribArray(0);

	// load IBO
	glGenBuffers(1, &mIbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIbo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLushort), indices.data(), GL_STATIC_DRAW);

	glGenTextures(1, &mTexObject);
	std::string texturePath = Ether::Core::EtherPlatform::GetInstance()->GetAssetsDirectory();
	texturePath += texPath;
	unsigned int texLoaded = sb7::ktx::file::load(texturePath.c_str(), mTexObject);
	if (texLoaded != mTexObject) {
		Ether::Core::EtherLog::GetInstance()->LogError("Could not load texture.");
	}

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(EtherVertPTN), BUFFER_OFFSET(24));
	glEnableVertexAttribArray(1);
}

EtherRenderable::~EtherRenderable() {
	glDeleteVertexArrays(1, &mVao);
	glDeleteProgram(mProgram);

	glDeleteBuffers(1, &mVbo);
	glDeleteBuffers(1, &mIbo);

	glDeleteTextures(1, &mTexObject);

	glDeleteProgram(mProgram);
}

void EtherRenderable::Render(double currentTime, const glm::mat4& mvMatrix, const glm::mat4& projMatrix)
{
	glUseProgram(mProgram);
	glBindVertexArray(mVao);

	glBindTexture(GL_TEXTURE_2D, mTexObject);

	// TODO: switch to LINEAR filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glUniformMatrix4fv(mModelViewLoc, 1, GL_FALSE, glm::value_ptr(mvMatrix));
	glUniformMatrix4fv(mProjLoc, 1, GL_FALSE, glm::value_ptr(projMatrix));
	glUniform1i(mTexLoc, 0);

	glDrawElements(GL_TRIANGLES, mVertCount, GL_UNSIGNED_SHORT, 0);
}
	
}
}