#pragma once
#include "imgui.h"
#include "Renderer.h"
#include "CCamera.h"
#include "ImGuizmo.h"

// calss abstraction of imGui
// takes CRenderer-pointer to render

class CGUI
{
private:
	ImGuiIO* io = new ImGuiIO;
	HWND* hWnd;
	ImGuizmo::OPERATION mCurrentGizmoOperation;
	ImGuizmo::MODE mCurrentGizmoMode;
	DirectX::XMMATRIX DeltaMatrix;
	DirectX::XMMATRIX GizmoMatrix;
	std::thread t_rGUI;
	class CRenderer* pRenderer = nullptr;
	class CCamera* camera;
	class CMesh* mSelected_model;
	void Manipulate(const DirectX::XMMATRIX *view, const DirectX::XMMATRIX *projection, DirectX::XMMATRIX *matrix, DirectX::XMMATRIX *deltaMatrix, float *snap, float *localBounds, float *boundsSnap);
	bool Gizmo = false;
	void(*GizmoCallback)(DirectX::XMMATRIX deltaMatrix);

public:
	CGUI();
	CGUI(CCamera& c);
	void InitGUI(class CRenderer* pRenderer, HWND &hWnd, void(*gizmoCallback)(DirectX::XMMATRIX deltaMatrix));
	void RenederGUI(void(*DrawGui)(void));
	void UpdateGUIScaling();
	void Shutdown();
	void Restart();
	void ShowGizmo(bool show, DirectX::XMMATRIX GizmoMat);
	void ShowGizmo(bool show);
	void GizmoTranslate();
	void GizmoRotate();
	void GizmoScale();
	void UpdateGuizmo();
	void SetGizmoPosition(float x, float y, float z);
	ImGuiIO GetIO();
	bool IsOver();
	~CGUI();
};

