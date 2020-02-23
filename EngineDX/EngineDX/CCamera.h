#pragma once
#include "Global.h"

class CCamera
{
private:
	float FOV;
	float BufferWidht;
	float BufferHeight;
	float NearPlane;
	float FarPlane;
	float Yaw;
	float Pitch;
	float MoveSpeed;
	float TurnSpeed;
	DirectX::XMVECTOR Position;
	DirectX::XMVECTOR WorldUp;
	DirectX::XMVECTOR ForwardVector;
	DirectX::XMVECTOR UpVector;
	DirectX::XMVECTOR RightVector;
	void ComputeVectors();

public:
	CCamera();
	CCamera(float fov,
		float bufWidth,
		float bufHeight,
		float nPlane,
		float fPlane,
		float yaw,
		float pitch,
		float moveSpeed,
		float turnSpeed,
		DirectX::XMVECTOR up,
		DirectX::XMVECTOR front,
		DirectX::XMVECTOR position);
	const DirectX::XMMATRIX GetProjectionMatrix();
	const DirectX::XMMATRIX GetViewMatrix();
	const DirectX::XMVECTOR GetCamerPosition();
	const DirectX::XMVECTOR GetForwardVector();
	const DirectX::XMVECTOR GetRightVector();

	// Key controls
	void MoveForward	(double deltaTime);
	void MoveBackward	(double deltaTime);
	void MoveRight		(double deltaTime);
	void MoveLeft		(double deltaTime);
	void MoveUp			(double deltaTime);
	void MoveDown		(double deltaTime);
	void Move			(double MovementX,
						 double MovementY,
						 double MovementZ);

	// Mouse controls
	void AddPitch		(float Angle);
	void AddYaw			(float Angle);
	void UpdateRotation	(float PitchAngle, float YawAngle);
	void UpdateContextRect(unsigned int w, unsigned int h);
	~CCamera();
};

