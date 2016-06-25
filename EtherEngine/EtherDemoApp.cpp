#include "EtherApp.h"

using namespace Ether;

class EtherDemoApp : public EtherApp
{
protected:
	void Startup() {
		EtherApp::Startup();

		mProgram = glCreateProgram();

		GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
		CompileShader(fs, "simple_tri_ps.glsl");

		GLuint vs = glCreateShader(GL_VERTEX_SHADER);
		CompileShader(vs, "simple_tri_vs.glsl");

		glAttachShader(mProgram, vs);
		glAttachShader(mProgram, fs);

		glLinkProgram(mProgram);

		glDeleteShader(fs);
		glDeleteShader(vs);

		glGenVertexArrays(1, &mVao);
		glBindVertexArray(mVao);
	}

	void Render(double currentTime) {
		EtherApp::Render(currentTime);

		static const GLfloat green[] = { 0.0f, 0.25f, 0.0f, 1.0f };
		glClearBufferfv(GL_COLOR, 0, green);

		glUseProgram(mProgram);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

	void Shutdown() {
		EtherApp::Shutdown();

		glDeleteVertexArrays(1, &mVao);
		glDeleteProgram(mProgram);
	}

private:
	GLuint mProgram;
	GLuint mVao;
};

DECLARE_MAIN(EtherDemoApp)