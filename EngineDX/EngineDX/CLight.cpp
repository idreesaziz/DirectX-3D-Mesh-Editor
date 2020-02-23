// most of the functions in CLight are virtual functions
// and are overriden in implementations (cpp) of the inherited classes

#include "pch.h"
#include "CLight.h"

CLight::CLight()
{
}

DirectX::XMFLOAT4 CLight::GetLightColor()
{
	return LightColor;
}

DirectX::XMFLOAT3A CLight::GetAmbientDown()
{
	// Viretual function
	return DirectX::XMFLOAT3A();
}

DirectX::XMFLOAT3A CLight::GetAmbientRange()
{
	// Viretual function
	return DirectX::XMFLOAT3A();
}

DirectX::XMFLOAT4 CLight::GetLightDirection()
{
	// Viretual function
	return DirectX::XMFLOAT4();
}

void CLight::SetLightColor(DirectX::XMFLOAT4 nLightColor)
{
	LightColor = nLightColor;
}

void CLight::SetAmbientDown(DirectX::XMFLOAT3A nAmbientDown)
{
	// Viretual function
}

void CLight::SetAmbientRange(DirectX::XMFLOAT3A nAmbientRange)
{
	// Viretual function
}

void CLight::SetLightDirection(DirectX::XMFLOAT4 nLightDirection)
{
	// Viretual function
}

CLight::~CLight()
{
}
