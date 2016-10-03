#pragma once

#include "EtherMath.h"

namespace Ether {
namespace Graphics {

class EtherCamera
{
public:
	EtherCamera();
	~EtherCamera();

	glm::mat4 GetView() const;

	void MoveRight();
	void MoveLeft();
	void MoveUp();
	void MoveDown();

private:
	glm::vec3 mPosition;
	glm::vec3 mTarget;;
	glm::vec3 mForward;
	glm::vec3 mRight;
	glm::vec3 mUp;
};

}
}

