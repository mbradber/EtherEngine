#include "EtherCamera.h"
#include "GLFW\glfw3.h"
#include "EtherLog.h"
#include <sstream>

namespace Ether {
namespace Graphics {

float EtherCamera::sMoveSpeed = 5.0f;

EtherCamera::EtherCamera()
	:mPosition(0.f, 0.f, 10.f), 
	mTarget(0.f, 0.f, 0.f), 
	mForward(0.f, 0.f, -1.f),
	mRight(1.f, 0.f, 0.f),
	mUp(0.f, 1.f, 0.f),
	mDeltaTime(0.f),
	mLastTime(0.f)
{
}

EtherCamera::~EtherCamera() {

}

glm::mat4 EtherCamera::GetView() const {
	glm::mat4 view;
	view = glm::lookAt(mPosition, mPosition + mForward, glm::vec3(0.f, 1.f, 0.f));
	return view;
}

void EtherCamera::MoveRight() {
	mPosition += mRight * mDeltaTime * sMoveSpeed;
}

void EtherCamera::MoveLeft() {
	mPosition -= mRight * mDeltaTime * sMoveSpeed;
}

void EtherCamera::MoveUp() {
	mPosition += mUp * mDeltaTime * sMoveSpeed;
}

void EtherCamera::MoveDown() {
	mPosition -= mUp * mDeltaTime * sMoveSpeed;
}

void EtherCamera::MoveForward() {
	mPosition += mForward * mDeltaTime * sMoveSpeed;
}

void EtherCamera::MoveBack() {
	mPosition -= mForward * mDeltaTime * sMoveSpeed;
}

void EtherCamera::UpdateInput(int key, int action) {
	if (action == GLFW_PRESS) {
		mKeys[key] = true;
	}
	else if (action == GLFW_RELEASE) {
		mKeys[key] = false;
	}
} 

void EtherCamera::Update(float currentTime) {
	mDeltaTime = currentTime - mLastTime;
	mLastTime = currentTime;

	if (mKeys[GLFW_KEY_D])
		MoveRight();
	if (mKeys[GLFW_KEY_A])
		MoveLeft();
	if (mKeys[GLFW_KEY_Q])
		MoveUp();
	if (mKeys[GLFW_KEY_E])
		MoveDown();
	if (mKeys[GLFW_KEY_W])
		MoveForward();
	if (mKeys[GLFW_KEY_S])
		MoveBack();
}


}
}
