#include "EtherApp.h"

using namespace Ether;

class EtherDemoApp : public EtherApp
{
protected:
	void Startup() {
		EtherApp::Startup();

		static const char * vs_source[] =
		{
			"#version 450 core                                                 \n"
			"                                                                  \n"
			"void main(void)                                                   \n"
			"{                                                                 \n"
			"    const vec4 vertices[] = vec4[](vec4( 0.25, -0.25, 0.5, 1.0),  \n"
			"                                   vec4(-0.25, -0.25, 0.5, 1.0),  \n"
			"                                   vec4( 0.25,  0.25, 0.5, 1.0)); \n"
			"                                                                  \n"
			"    gl_Position = vertices[gl_VertexID];                          \n"
			"}                                                                 \n"
		};

		static const char * fs_source[] =
		{
			"#version 450 core                                                 \n"
			"                                                                  \n"
			"out vec4 color;                                                   \n"
			"                                                                  \n"
			"void main(void)                                                   \n"
			"{                                                                 \n"
			"    color = vec4(0.0, 0.8, 1.0, 1.0);                             \n"
			"}                                                                 \n"
		};

		mProgram = glCreateProgram();
		GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fs, 1, fs_source, NULL);
		glCompileShader(fs);

		GLuint vs = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vs, 1, vs_source, NULL);
		glCompileShader(vs);

		glAttachShader(mProgram, vs);
		glAttachShader(mProgram, fs);

		glLinkProgram(mProgram);

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
		glDeleteVertexArrays(1, &mVao);
		glDeleteProgram(mProgram);
	}

private:
	GLuint mProgram;
	GLuint mVao;
};

DECLARE_MAIN(EtherDemoApp)