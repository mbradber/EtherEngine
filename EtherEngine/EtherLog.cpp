#include "EtherLog.h"
#include <Windows.h>

namespace Ether {
namespace Core {

EtherLog* EtherLog::mInstance = nullptr;

void EtherLog::LogError(const std::string& msg) {
	OutputDebugStringA(msg.c_str());
}

void EtherLog::LogInfo(const std::string& msg) {
	OutputDebugStringA(msg.c_str());
}

}
}