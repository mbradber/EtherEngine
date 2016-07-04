#include "EtherApp.h"
#include "EtherPlatform.h"
#include "EtherLog.h"
#include <fstream>
#include <vector>
#include <sstream>

Ether::Core::EtherApp* Ether::Core::EtherApp::mApp = 0;

namespace Ether {
namespace Core {

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


void EtherApp::CompileShader(GLuint shader, const std::string& shaderPath) {
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
		std::stringstream ss;
		ss << "Error loading file contents from " << shaderPath << std::endl;
		EtherLog::GetInstance()->LogError(ss.str());
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

		EtherLog::GetInstance()->LogError(errorStr);
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
}