#pragma once

#include <Windows.h>
#include "GL/gl3w.h"

#define GLFW_NO_GLU 1
#define GLFW_INCLUDE_GLCOREARB 1

#include "GLFW/glfw3.h"
#include <string>

#include "EtherLog.h"

namespace Ether {
namespace Core {

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
		glfwSetCursorPosCallback(mWindow, GLFW_OnCursorPos);
		//glfwSetInputMode(mWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		gl3wInit();

#if DEBUG
		glDebugMessageCallback((GLDEBUGPROC)DebugCallback, this);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
#endif

		Startup();

		do {
			Render(glfwGetTime());

			glfwSwapBuffers(mWindow);
			glfwPollEvents();

			running &= (glfwGetKey(mWindow, GLFW_KEY_ESCAPE) == GLFW_RELEASE);
			running &= (glfwWindowShouldClose(mWindow) != GL_TRUE);
		} while (running);

		Shutdown();

		glfwDestroyWindow(mWindow);
		glfwTerminate();
	}

	static void EtherApp::CompileShader(GLuint shader, const std::string& shaderPath);
	static void EtherApp::CheckLinkStatus(GLuint program);

protected:

	virtual void Init() {
		mWindowTitle = "EtherEngine";
		mWindowWidth = 800;
		mWindowHeight = 600;
		mSamples = 0;
	}

	virtual void Startup() {

	}

	virtual void Render(double currentTime) {

	}

	virtual void Shutdown();

	virtual void OnResize(size_t w, size_t h) {
		mWindowWidth = w;
		mWindowHeight = h;
	}

	virtual void SetWindowTitle(const std::string& subtext);

	virtual void OnKey(int key, int action) {

	}

	virtual void OnCursorPos(double xpos, double ypos) {
	
	}

	virtual void OnDebugMessage(GLenum source,
		GLenum type,
		GLuint id,
		GLenum severity,
		GLsizei length,
		const GLchar* message)
	{
#ifdef _WIN32
		OutputDebugStringA(message);
		OutputDebugStringA("\n");
#endif /* _WIN32 */
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

	static void GLFW_OnCursorPos(GLFWwindow* window, double xpos, double ypos) {
		mApp->OnCursorPos(xpos, ypos);
	}

	GLFWwindow* mWindow;
	static EtherApp* mApp;

protected:

	size_t mWindowWidth;
	size_t mWindowHeight;
	size_t mSamples;
	std::string mWindowTitle;
};

}
}


#define DECLARE_MAIN(a)                             \
Ether::Core::EtherApp *app = 0;                           \
int CALLBACK WinMain(HINSTANCE hInstance,           \
                     HINSTANCE hPrevInstance,       \
                     LPSTR lpCmdLine,               \
                     int nCmdShow)                  \
{                                                   \
    app = new a;                                    \
    app->Run(app);                                  \
    delete app;                                     \
    return 0;                                       \
}