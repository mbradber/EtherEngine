#include "EtherCubeRO.h"
#include "EtherApp.h"
#include "EtherGeometry.h"
#include "EtherPlatform.h"
#include "sb7ktx.h"

namespace Ether {
namespace Renderables {

EtherCubeRO::EtherCubeRO(const std::string& texture) {
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

	Ether::Core::EtherVert_Pos_Tex verts[] = {
		{ { -1, -1, 1 },{ 0, 0 } },
		{ { 1, -1, 1 },{ 1, 0 } },
		{ { 1, 1, 1 },{ 1, 1 } },
		{ { -1, 1, 1 },{ 0, 1 } },

		{ { 1, -1, 1 },{ 0, 0 } },
		{ { 1, -1, -1 },{ 1, 0 } },
		{ { 1, 1, -1 },{ 1, 1 } },
		{ { 1, 1, 1 },{ 0, 1 } },

		{ { 1, -1, -1 },{ 0, 0 } },
		{ { -1, -1, -1 },{ 1, 0 } },
		{ { -1, 1, -1 },{ 1, 1 } },
		{ { 1, 1, -1 },{ 0, 1 } },

		{ { -1, -1, -1 },{ 0, 0 } },
		{ { -1, -1, 1 },{ 1, 0 } },
		{ { -1, 1, 1 },{ 1, 1 } },
		{ { -1, 1, -1 },{ 0, 1 } },

		{ { -1, 1, 1 },{ 0, 0 } },
		{ { 1, 1, 1 },{ 1, 0 } },
		{ { 1, 1, -1 },{ 1, 1 } },
		{ { -1, 1, -1 },{ 0, 1 } },

		{ { 1, -1, -1 },{ 0, 0 } },
		{ { 1, -1, 1 },{ 1, 0 } },
		{ { -1, -1, 1 },{ 1, 1 } },
		{ { -1, -1, -1 },{ 0, 1 } }
	};

	GLushort indices[] = {
		0, 1, 2,
		2, 3, 0,

		4, 5, 6,
		6, 7, 4,

		8, 9, 10,
		10, 11, 8,

		12, 13, 14,
		14, 15, 12,

		16, 17, 18,
		18, 19, 16,

		20, 21, 22,
		22, 23, 20,
	};

	glGenBuffers(1, &mVbo);
	glBindBuffer(GL_ARRAY_BUFFER, mVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Ether::Core::EtherVert_Pos_Tex), NULL);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &mIbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIbo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glGenTextures(1, &mTexObject);
	std::string texturePath = Ether::Core::EtherPlatform::GetInstance()->GetAssetsDirectory();
	texturePath += texture;
	sb7::ktx::file::load(texturePath.c_str(), mTexObject);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Ether::Core::EtherVert_Pos_Tex), BUFFER_OFFSET(12));
	glEnableVertexAttribArray(1);
}


EtherCubeRO::~EtherCubeRO() {
	glDeleteVertexArrays(1, &mVao);
	glDeleteProgram(mProgram);

	glDeleteBuffers(1, &mVbo);
	glDeleteBuffers(1, &mIbo);

	glDeleteTextures(1, &mTexObject);

	glDeleteProgram(mProgram);
}


void EtherCubeRO::Render(double currentTime, const glm::mat4& mvMatrix, const glm::mat4& projMatrix) {
	// set this objects shader program and bind its VAO
	glUseProgram(mProgram);
	glBindVertexArray(mVao);

	// bind and set texture params
	glBindTexture(GL_TEXTURE_2D, mTexObject);

	// TODO: switch to LINEAR filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// set shader uniforms
	glUniformMatrix4fv(mModelViewLoc, 1, GL_FALSE, glm::value_ptr(mvMatrix));
	glUniformMatrix4fv(mProjLoc, 1, GL_FALSE, glm::value_ptr(projMatrix));
	glUniform1i(mTexLoc, 0); // tell sampler to look at 2d texture bound on texture unit 0

	 // draw
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0);
}

}
}


