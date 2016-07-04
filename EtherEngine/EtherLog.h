#pragma once

#include <iostream>
#include <string>

namespace Ether {
namespace Core {

class EtherLog
{
public:
	static EtherLog* GetInstance() {
		if (mInstance = nullptr) {
			mInstance = new EtherLog();
		}

		return mInstance;
	}

	void Release() {
		if (mInstance) {
			delete mInstance;
		}
	}

	void LogError(const std::string& msg);

private:
	static EtherLog* mInstance;

	EtherLog() {

	}

	~EtherLog() {

	}
};

}
}