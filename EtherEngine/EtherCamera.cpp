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
	mLastTime(0.f),
	mYaw(-90.f),
	mPitch(0.f),
	mLastInputX(0.f),
	mLastInputY(0.f),
	mFirstInput(true),
	mSensitivity(0.1f),
	mDirectionCapture(false)
{
}

EtherCamera::~EtherCamera() {

}

glm::mat4 EtherCamera::GetView() const {
	glm::mat4 view;
	view = glm::lookAt(mPosition, mPosition + mForward, mUp);
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

void EtherCamera::UpdateMovement(int key, int action) {
	if (action == GLFW_PRESS) {
		mKeys[key] = true;
	}
	else if (action == GLFW_RELEASE) {
		mKeys[key] = false;
	}
} 

void EtherCamera::UpdateDirection(double xpos, double ypos) {
	if (!mDirectionCapture)
		return;

	if (mFirstInput) {
		mLastInputX = xpos;
		mLastInputY = ypos;

		mFirstInput = false;
	}

	float xoffset = xpos - mLastInputX;
	float yoffset = mLastInputY - ypos;
	mLastInputX = xpos;
	mLastInputY = ypos;

	xoffset *= mSensitivity;
	yoffset *= mSensitivity;

	mYaw += xoffset;
	mPitch += yoffset;

	if (mPitch > 89.f)
		mPitch = 89.f;
	if (mPitch < -89.f)
		mPitch = -89.f;

	glm::vec3 front;
	front.x = cos(glm::radians(mYaw)) * cos(glm::radians(mPitch));
	front.y = sin(glm::radians(mPitch));
	front.z = sin(glm::radians(mYaw)) * cos(glm::radians(mPitch));

	mForward = glm::normalize(front);
	mRight = glm::cross(mForward, mUp);
}

void EtherCamera::Update(float currentTime) {
	mDeltaTime = currentTime - mLastTime;
	mLastTime = currentTime;

	if (mKeys[GLFW_KEY_D])
		MoveRight();
	if (mKeys[GLFW_KEY_A])
		MoveLeft();
	if (mKeys[GLFW_KEY_Q])
		MoveDown();
	if (mKeys[GLFW_KEY_E])
		MoveUp();
	if (mKeys[GLFW_KEY_W])
		MoveForward();
	if (mKeys[GLFW_KEY_S])
		MoveBack();
}

void EtherCamera::DirectionCapture(bool capture) {
	if (!capture) {
		mFirstInput = true;
	}

	mDirectionCapture = capture;
}


}
}
