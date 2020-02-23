#include "pch.h"
#include "CLight.h"


// Getters
DirectX::XMFLOAT3A CHemisphericLight::GetAmbientDown()
{
	return AmbientDown;
}
DirectX::XMFLOAT3A CHemisphericLight::GetAmbientRange()
{
	return AmbientRange;
}

// Setters
void CHemisphericLight::SetAmbientDown(DirectX::XMFLOAT3A nAmbientDown)
{
	AmbientDown = nAmbientDown;
}
void CHemisphericLight::SetAmbientRange(DirectX::XMFLOAT3A nAmbientRange)
{
	AmbientRange = nAmbientRange;
}