#pragma once

#include <Windows.h>
#include "GL/gl3w.h"

#define GLFW_NO_GLU 1
#define GLFW_INCLUDE_GLCOREARB 1

#include "GLFW/glfw3.h"
#include <string>

#include "EtherLog.h"

namespace Ether
{

class EtherApp
{
public:

	EtherApp() {}
	virtual ~EtherApp() {}

	virtual void Run(EtherApp* app) {
		bool running = true;
		mApp = app;

		if (!glfwInit()) {
			EtherLog::GetInstance()->LogError("Failed to initialize GLFW\n");
			return;
		}

		Init();

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);

#if DEBUG
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
#endif

		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_SAMPLES, static_cast<int>(mSamples));
		glfwWindowHint(GLFW_STEREO, GL_FALSE);

		mWindow = glfwCreateWindow(mWindowWidth, mWindowHeight, mWindowTitle.c_str(), NULL, NULL);

		if (!mWindow) {
			EtherLog::GetInstance()->LogError("Failed to open window\n");
			return;
		}

		glfwMakeContextCurrent(mWindow);

		glfwSetWindowSizeCallback(mWindow, GLFW_OnResize);
		glfwSetKeyCallback(mWindow, GLFW_OnKey);

		gl3wInit();
	}

protected:

	virtual void Init() {
		mWindowTitle = "EtherEngine Application";
		mWindowWidth = 800;
		mWindowHeight = 600;
		mSamples = 0;
	}

	virtual void OnResize(size_t w, size_t h) {
		mWindowWidth = w;
		mWindowHeight = h;
	}

	virtual void OnKey(int key, int action) {

	}

private:

	static void APIENTRY DebugCallback(GLenum source,
		GLenum type,
		GLuint id,
		GLenum severity,
		GLsizei length,
		const GLchar* message,
		GLvoid* userParam);

	static void GLFW_OnResize(GLFWwindow* window, int w, int h) {
		mApp->OnResize(w, h);
	}

	static void GLFW_OnKey(GLFWwindow* window, int key, int scancode, int action, int mods) {
		mApp->OnKey(key, action);
	}

	GLFWwindow* mWindow;
	static EtherApp* mApp;
	size_t mWindowWidth;
	size_t mWindowHeight;
	size_t mSamples;
	std::string mWindowTitle;
};

}






#define DECLARE_MAIN(a)                             \
sb7::application *app = 0;                          \
int CALLBACK WinMain(HINSTANCE hInstance,           \
                     HINSTANCE hPrevInstance,       \
                     LPSTR lpCmdLine,               \
                     int nCmdShow)                  \
{                                                   \
    a *app = new a;                                 \
    app->run(app);                                  \
    delete app;                                     \
    return 0;                                       \
}