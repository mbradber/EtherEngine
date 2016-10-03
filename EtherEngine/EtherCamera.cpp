#include "EtherCamera.h"
#include "GLFW\glfw3.h"

namespace Ether {
namespace Graphics {


EtherCamera::EtherCamera()
	:mPosition(0.f, 0.f, 10.f), 
	mTarget(0.f, 0.f, 0.f), 
	mForward(0.f, 0.f, -1.f),
	mRight(1.f, 0.f, 0.f),
	mUp(0.f, 1.f, 0.f)
{
}


EtherCamera::~EtherCamera() {

}

glm::mat4 EtherCamera::GetView() const {
	glm::mat4 view;
	view = glm::lookAt(mPosition, glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f));
	return view;
}

void EtherCamera::MoveRight() {
	mPosition += mRight * (float)glfwGetTime() * 0.1f;
}

void EtherCamera::MoveLeft() {
	mPosition += mRight * (float)glfwGetTime() * -0.1f;
}

void EtherCamera::MoveUp() {
	mPosition += mUp * 0.1f;
}

void EtherCamera::MoveDown() {
	mPosition += mUp * -0.1f;
}

}
}
