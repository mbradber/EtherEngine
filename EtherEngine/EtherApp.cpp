#include "EtherApp.h"

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

}