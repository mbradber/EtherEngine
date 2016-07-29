#include "EtherApp.h"
#include "EtherCubeRO.h"

class SpinnyCube : public Ether::Core::EtherApp
{
protected:
	void Startup() {
		EtherApp::Startup();

		mCube = new Ether::Renderables::EtherCubeRO("ktx/brick.ktx");

		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
	}

	void Render(double currentTime) {
		EtherApp::Render(currentTime);

		static const GLfloat green[] = { 0.0f, 0.25f, 0.0f, 1.0f };
		static const GLfloat one = 1.0f;

		glViewport(0, 0, mWindowWidth, mWindowHeight);
		glClearBufferfv(GL_COLOR, 0, green);
		glClearBufferfv(GL_DEPTH, 0, &one);

		float f = (float)currentTime * 0.3f;
		vmath::mat4 mvMatrix = vmath::translate(0.0f, 0.0f, -4.0f) *
			vmath::translate(sinf(2.1f * f) * 0.5f,
				cosf(1.7f * f) * 0.5f,
				sinf(1.3f * f) * cosf(1.5f * f) * 2.0f) *
			vmath::rotate((float)currentTime * 45.0f, 0.0f, 1.0f, 0.0f) *
			vmath::rotate((float)currentTime * 81.0f, 1.0f, 0.0f, 0.0f);
		vmath::mat4 projMatrix = vmath::perspective(50.0f, (float)mWindowWidth / (float)mWindowHeight, 0.1f, 1000.0f);

		mCube->Render(currentTime, mvMatrix, projMatrix);
	}

	void Shutdown() {
		EtherApp::Shutdown();
		delete mCube;
	}

private:
	Ether::Renderables::EtherCubeRO* mCube;
};

//DECLARE_MAIN(SpinnyCube)