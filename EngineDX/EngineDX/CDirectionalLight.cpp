#include "pch.h"
#include "CLight.h"

DirectX::XMFLOAT4 CDirectionalLight::GetLightDirection()
{
	return LightDirection;
}
void CDirectionalLight::SetLightDirection(DirectX::XMFLOAT4 nLightDirection)
{
	LightDirection = nLightDirection;
}

void CDirectionalLight::RotateYaw(float degree)
{
	LightDirection.y += degree;
}

void CDirectionalLight::RotatePitch(float degree)
{
	LightDirection.x += degree;
}

void CDirectionalLight::AttachToCamera(DirectX::XMVECTOR CameraPosition)
{
	LightDirection.x = CameraPosition.m128_f32[0];
	LightDirection.y = CameraPosition.m128_f32[1];
	LightDirection.z = CameraPosition.m128_f32[2];
}
