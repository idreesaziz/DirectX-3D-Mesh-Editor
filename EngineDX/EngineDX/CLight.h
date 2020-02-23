#pragma once

//----------------------------------------------------------------------------------------------------------
// CLight BaseClass ----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
class CLight
{
protected:
	float Intensity = 1.f; 
	DirectX::XMFLOAT4 LightColor;

public:

	CLight();

	// Getters
	DirectX::XMFLOAT4 GetLightColor();
	virtual DirectX::XMFLOAT3A GetAmbientDown();
	virtual DirectX::XMFLOAT3A GetAmbientRange();
	virtual DirectX::XMFLOAT4 GetLightDirection();

	// Setters
	void SetLightColor(DirectX::XMFLOAT4 nLightColor);
	virtual void SetAmbientDown(DirectX::XMFLOAT3A nAmbientDown);
	virtual void SetAmbientRange(DirectX::XMFLOAT3A nAmbientRange);
	virtual void SetLightDirection(DirectX::XMFLOAT4 nLightDirection);

	~CLight();
};


//----------------------------------------------------------------------------------------------------------
// HemisphericLight ----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
class CHemisphericLight : public CLight
{
private:
	DirectX::XMFLOAT3A AmbientDown;
	DirectX::XMFLOAT3A AmbientRange;

public:
	// Getters
	DirectX::XMFLOAT3A GetAmbientDown() override;
	DirectX::XMFLOAT3A GetAmbientRange() override;
	
	// Setters
	void SetAmbientDown(DirectX::XMFLOAT3A nAmbientDown) override;
	void SetAmbientRange(DirectX::XMFLOAT3A nAmbientRange) override;
};


//----------------------------------------------------------------------------------------------------------
// DirectionalLight ----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
class CDirectionalLight : public CLight
{
private:
	DirectX::XMFLOAT4 LightDirection;

public:
	DirectX::XMFLOAT4 GetLightDirection() override;
	void SetLightDirection(DirectX::XMFLOAT4 nLightDirection) override;
	void RotateYaw(float degree);
	void RotatePitch(float degree);
	void AttachToCamera(DirectX::XMVECTOR CameraPosition);
};


//----------------------------------------------------------------------------------------------------------
// CLightingModel ------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
struct CLightingModel 
{
	CHemisphericLight HemisphericLight;
	CDirectionalLight DirectionalLight;
};