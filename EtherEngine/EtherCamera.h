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
	void MoveForward();
	void MoveBack();

	void Update(float currentTime);
	void UpdateMovement(int key, int action);
	void UpdateDirection(double xpos, double ypos);
	void DirectionCapture(bool);

private:
	glm::vec3 mPosition;
	glm::vec3 mTarget;;
	glm::vec3 mForward;
	glm::vec3 mRight;
	glm::vec3 mUp;

	bool mKeys[1024] = { false };

	float mDeltaTime;
	float mLastTime;

	float mYaw;
	float mPitch;
	float mLastInputX;
	float mLastInputY;
	float mSensitivity;
	bool mFirstInput;
	bool mDirectionCapture;

	static float sMoveSpeed;
};

}
}

