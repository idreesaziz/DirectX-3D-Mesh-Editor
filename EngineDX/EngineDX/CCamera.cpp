#include "pch.h"
#include "CCamera.h"
#include "Window.h"

using namespace DirectX;


CCamera::CCamera()
{
}

CCamera::CCamera(float fov,
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
				 DirectX::XMVECTOR position)
	:
	FOV						(fov),
	BufferWidht				(bufWidth),
	BufferHeight			(bufHeight),
	NearPlane				(nPlane),
	FarPlane				(fPlane),
	Yaw						(yaw),
	Pitch					(pitch),
	MoveSpeed				(moveSpeed),
	TurnSpeed				(turnSpeed),
	Position				(position),
	WorldUp					(up),
	ForwardVector			(front),
	UpVector				(up)
{
	ComputeVectors();
}

const DirectX::XMMATRIX CCamera::GetProjectionMatrix()
{
	return XMMatrixPerspectiveFovLH(math::ToRadians(FOV), BufferWidht / BufferHeight, NearPlane, FarPlane);
}

const DirectX::XMMATRIX CCamera::GetViewMatrix()
{
	return XMMatrixLookAtLH(Position, Position + ForwardVector, UpVector);
}

const DirectX::XMVECTOR CCamera::GetCamerPosition()
{
	return Position;
}

const DirectX::XMVECTOR CCamera::GetForwardVector()
{
	return ForwardVector;
}

const DirectX::XMVECTOR CCamera::GetRightVector()
{
	return RightVector;
}

// Keyboard controls
void CCamera::MoveForward	(double deltaTime)	{	Position += ForwardVector * MoveSpeed;	}
void CCamera::MoveBackward	(double deltaTime)	{	Position -= ForwardVector * MoveSpeed;	}
void CCamera::MoveLeft		(double deltaTime)	{	Position += RightVector * MoveSpeed;	}
void CCamera::MoveRight		(double deltaTime)	{	Position -= RightVector	* MoveSpeed;	}
void CCamera::MoveUp		(double deltaTime)	{	Position += UpVector * MoveSpeed;		}
void CCamera::MoveDown		(double deltaTime)	{	Position -= UpVector * MoveSpeed;		}

void CCamera::Move(double MovementX, double MovementY, double MovementZ)
{
	Position -= RightVector * MovementX * 0.01;
	Position -= UpVector * MovementY * 0.01;
}

// Mouse Controls
void CCamera::AddPitch	(float Angle) { Pitch	-= Angle * TurnSpeed;	ComputeVectors();	}
void CCamera::AddYaw	(float Angle) {	Yaw		-= Angle * TurnSpeed;	ComputeVectors();	}

void CCamera::UpdateRotation(float PitchAngle, float YawAngle)
{
	Pitch += PitchAngle * TurnSpeed;
	Yaw += YawAngle * TurnSpeed;
	ComputeVectors();
}

void CCamera::UpdateContextRect(unsigned int w, unsigned int h)
{
	BufferWidht = w;
	BufferHeight = h;
}

void CCamera::ComputeVectors()
{
	ForwardVector = XMVectorSet(cos(math::ToRadians(Yaw)) * cos(math::ToRadians(Pitch)),
						sin(math::ToRadians(Pitch)),
						sin(math::ToRadians(Yaw)) * cos(math::ToRadians(Pitch)),
						0.f);
	ForwardVector	= XMVector4Normalize(ForwardVector);
	RightVector		= XMVector4Normalize(DirectX::XMVector3Cross(ForwardVector, WorldUp));
	UpVector		= XMVector4Normalize(DirectX::XMVector3Cross(RightVector, ForwardVector));
}


CCamera::~CCamera()
{
}
