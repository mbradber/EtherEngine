#pragma once

#include <string>

namespace Ether {
namespace Core {

class EtherPlatform
{
public:
	static EtherPlatform* GetInstance() {
		if (mInstance = nullptr) {
			mInstance = new EtherPlatform();
		}

		return mInstance;
	}

	void Release() {
		if (mInstance != nullptr) {
			delete mInstance;
		}
	}

	std::string GetAssetsDirectory() const;

private:
	static EtherPlatform* mInstance;

	EtherPlatform() {

	}

	~EtherPlatform() {

	}
};


}
}