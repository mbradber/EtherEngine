#include "EtherApp.h"
#include "EtherPlatform.h"
#include "EtherLog.h"
#include <fstream>
#include <vector>

Ether::EtherApp* Ether::EtherApp::mApp = 0;

namespace Ether 
{
	void APIENTRY EtherApp::DebugCallback(GLenum source,
			GLenum type,
			GLuint id,
			GLenum severity,
			GLsizei length,
			const GLchar* message,
			GLvoid* userParam)
	{
		reinterpret_cast<EtherApp*>(userParam)->OnDebugMessage(source, type, id, severity, length, message);
	}


	void EtherApp::CompileShader(GLuint shader, const std::string& shaderPath) const {
		std::string assetsDir = EtherPlatform::GetInstance()->GetAssetsDirectory();
		if (assetsDir.empty()) {
			return;
		}

		std::string tmpShaderPath = assetsDir + "shaders/" + shaderPath;
		std::string shaderString;
		std::ifstream sourceFile(tmpShaderPath.c_str());

		if (sourceFile) {
			shaderString.assign((std::istreambuf_iterator< char >(sourceFile)), std::istreambuf_iterator< char >());
		}
		else {
			// TODO: move to EtherLog
			std::cout << "Error loading file contents from " << shaderPath << std::endl;
			return;
		}

		const GLchar* shaderSource = shaderString.c_str();

		// load/compile shader
		glShaderSource(shader, 1, (const GLchar**)&shaderSource, NULL);
		glCompileShader(shader);

		GLint isCompiled = 0;

		glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);

		if (isCompiled == GL_FALSE) {
			GLint maxLength = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> errorLog(maxLength);
			glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);
			std::string errorStr(errorLog.begin(), errorLog.end());

			// TODO: Use EtherLog and update it to use OutputDebugString
			OutputDebugStringA(errorStr.c_str());
		}
	}

	void EtherApp::Shutdown() {
		glfwDestroyWindow(mWindow);
		glfwTerminate();

		// TODO: make this smarter, register singletons or services or something to be cleaned up
		EtherPlatform::GetInstance()->Release();
		EtherLog::GetInstance()->Release();
	}

}