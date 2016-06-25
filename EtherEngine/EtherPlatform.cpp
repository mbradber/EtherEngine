#include "EtherPlatform.h"

namespace Ether 
{

EtherPlatform* EtherPlatform::mInstance = nullptr;

// TODO: make this more intelligent / not hard-coded
std::string EtherPlatform::GetAssetsDirectory() const {
	return "C:/Users/macobr/dev/EtherEngine/assets/";
}

}