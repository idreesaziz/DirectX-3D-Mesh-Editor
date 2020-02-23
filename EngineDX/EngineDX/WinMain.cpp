#pragma once

#include "pch.h"
#include "Global.h"

// all the global objects used in this cpp are declared in main.h
#include "Main.h" 
#include "DrawGui.h"

// Function prototypes
static void InitPipeline();
static void EventTick();
static void RenderFrame(void);
static void PickObject();
static void PickVertex();
static void PickFace();

// Callbacks
static void MouseCallback(EventType EType);
static void KeyCallback(EventType EType);
static void WindowCallback(EventType EType);
static void GizmoCallback(DirectX::XMMATRIX m);

// local functions
static void UpdateSolidShaderCB(unsigned int i);
static void UpdateWireframeShaderCB(unsigned int i);
static void UpdateVeretxOverlayShaderCB(unsigned int i);
static void UpdateFaceShaderCB(unsigned int i);
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Entry point ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// Initializing window
	SWindow.InitializeWindow(SWindow.GetDesktopReoslution(),		// Window dimensions
							 hInstance,								// WinAPI HInstance
							 "WindowClass1",						// Window Class name
							 "Engine",								// Window Title
							 0,										// Window back color
							 nCmdShow);								// WinAPI nCmdShow

	// Initializing the renderer
	SRenderer.InitializeRenderer(*SWindow.GetHWindow(),
							      SWindow.GetWindowHeight(),
							      SWindow.GetWindowWidth());
	InitPipeline();

	// Initializing window event callbacks
	SWindow.SetMouseCallback				(&MouseCallback);
	SWindow.SetKeyCallback					(&KeyCallback);
	SWindow.SetWindowCallback				(&WindowCallback);

	
	// Tnitializing gui
	SGUI.InitGUI(&SRenderer, *SWindow.GetHWindow(), &GizmoCallback);
	
	// Initializing the tick event
	SWindow.BeginTick(&EventTick);
	
	SGUI.Shutdown();
	return SWindow.GetMsg()->wParam;
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void UpdateShaderString()
{
	vProjectedMeshString.reserve(vMeshString.size());
	for (int i = 0; i < vMeshString.size(); i++)
	{
		// Reserving memory for projected vertices
		vProjectedMeshString.emplace_back(SProjectedMesh());
		vProjectedMeshString[i].verts.reserve(vMeshString[i].GetVerticesCount());

		// Creating solid shader...
		{
			CSolidShader s_shader;
				s_shader.SetRendererObject(&SRenderer);															// Binding renderer object to the shader
				s_shader.CreateShaderObject("DefaultShader.shader", "VShader", "GShader", "PShader");
				s_shader.CreateVertexBuffers(vMeshString[i].GetVertices(), vMeshString[i].GetVerticesSize());	// Creating vertex buffers...
				s_shader.CreateIndexBuffers(vMeshString[i].GetIndices(), vMeshString[i].GetIndicesSize());		// Creating index buffers...
				s_shader.CreateCB1();																			// Creating constant buffers...
				s_shader.CreateCB2();																			// Creating constant buffers...
			vSolidShaderString.push_back(s_shader);
		}

		// Creating wireframe shader...
		{
			CWireframeShader w_shader;
				w_shader.SetRendererObject(&SRenderer);
				w_shader.CreateShaderObject("WireframeShader.shader", "WIREFRAME_VS", "WIREFRAME_GS", "WIREFRAME_PS");
				w_shader.CreateVertexBuffers(vMeshString[i].GetVertices(), vMeshString[i].GetVerticesSize());
				w_shader.CreateIndexBuffers(vMeshString[i].GetIndices(), vMeshString[i].GetIndicesSize());
				w_shader.CreateCB1();
				w_shader.CreateCB2();
			vWireframeShaderString.push_back(w_shader);
		}

		// Creating vertex overlay shader...
		{
			CVertexOverlayShader v_shader;
			v_shader.SetRendererObject(&SRenderer);
			v_shader.CreateShaderObject("VertexOverlayShader.shader", "VS", "GS", "PS");
			v_shader.CreateVertexBuffers(vMeshString[i].GetVertices(), vMeshString[i].GetVerticesSize());
			v_shader.CreateIndexBuffers(vMeshString[i].GetIndices(), vMeshString[i].GetIndicesSize());
			v_shader.CreateCB1();
			v_shader.CreateCB2();
			vVertexShaderString.push_back(v_shader);
		}

		// Creating face solid shader...
		{
			CSolidShader sf_shader;
				sf_shader.SetRendererObject(&SRenderer);															// Binding renderer object to the shader
				sf_shader.CreateShaderObject("FaceOverlayShader.shader", "VShader", "GShader", "PShader");
				sf_shader.CreateVertexBuffers(vMeshString[i].GetVertices(), vMeshString[i].GetVerticesSize());		// Creating vertex buffers...
				sf_shader.CreateIndexBuffers(vMeshString[i].GetIndices(), vMeshString[i].GetIndicesSize());			// Creating index buffers...
				sf_shader.CreateCB1();																				// Creating constant buffers...
				sf_shader.CreateCB2();																				// Creating constant buffers...
			vFaceShaderString.push_back(sf_shader);
		}

		// Updating solid shader constant buffers...
		{
			CB_SolidTick cb;
				cb.mWorld			= XMMatrixTranspose(vMeshString[i].GetModelMatrix());
				cb.mView			= XMMatrixTranspose(SCamera.GetViewMatrix());
				cb.vLightColor		= SLightingModel.DirectionalLight.GetLightColor();
				cb.vLightDirection	= SLightingModel.DirectionalLight.GetLightDirection();
			vSolidShaderString[i].UpdateCB1(&cb);

			CB_SolidOnEvent ecb;
				ecb.mProjection		= XMMatrixTranspose(SCamera.GetProjectionMatrix());
				ecb.AmbientDown		= SLightingModel.HemisphericLight.GetAmbientDown();
				ecb.AmbientRange	= SLightingModel.HemisphericLight.GetAmbientRange();
			vSolidShaderString[i].UpdateCB2(&ecb);
		}

		// Updating wireframe constant buffers...
		{
			CB_WireframeTick cb;
				cb.mWorld			= XMMatrixTranspose(vMeshString[i].GetModelMatrix());
				cb.mView			= XMMatrixTranspose(SCamera.GetViewMatrix());
			vWireframeShaderString[i].UpdateCB1(&cb);

			CB_WireframeOnEvent ecb;
				ecb.mProjection		= XMMatrixTranspose(SCamera.GetProjectionMatrix());
			vWireframeShaderString[i].UpdateCB2(&ecb);
		}

		// Updating vertex overlay buffers...
		{
			CB_WireframeTick cb;
				cb.mWorld	= XMMatrixTranspose(vMeshString[i].GetModelMatrix());
				cb.mView	= XMMatrixTranspose(SCamera.GetViewMatrix());
			vVertexShaderString[i].UpdateCB1(&cb);

			CB_WireframeOnEvent ecb;
				ecb.mProjection = XMMatrixTranspose(SCamera.GetProjectionMatrix());
			vVertexShaderString[i].UpdateCB2(&ecb);
		}

		// Updating face overlay shader constant buffers...
		{
			CB_SolidTick cb;
				cb.mWorld			= XMMatrixTranspose(vMeshString[i].GetModelMatrix());
				cb.mView			= XMMatrixTranspose(SCamera.GetViewMatrix());
				cb.vLightColor		= SLightingModel.DirectionalLight.GetLightColor();
				cb.vLightDirection	= SLightingModel.DirectionalLight.GetLightDirection();
			vFaceShaderString[i].UpdateCB1(&cb);

			CB_SolidOnEvent ecb;
				ecb.mProjection		= XMMatrixTranspose(SCamera.GetProjectionMatrix());
				ecb.AmbientDown		= SLightingModel.HemisphericLight.GetAmbientDown();
				ecb.AmbientRange	= SLightingModel.HemisphericLight.GetAmbientRange();
			vFaceShaderString[i].UpdateCB2(&ecb);
		}

	}
}

static void InitPipeline()
{
	// Setting-up the camera
	SCamera = CCamera(45.f,														// FOV
					  SWindow.GetWindowWidth(),									// Context Width
					  SWindow.GetWindowHeight(),								// Context Height 
					  0.01f,													// Near plane
					  600.f,													// Far plane
					  90.f,														// Yaw
					  0.f,														// Pitch
					  0.5f,														// Move speed
					  0.1,														// Turn speed
					  DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f),				// UpVector
					  DirectX::XMVectorSet(0.f, 0.0f, 1.0f, 0.0f),				// ForwardVector
					  DirectX::XMVectorSet(3.f, 3.0f, -35.0f, 0.0f));			// Start position

	// Hemispheric light
	SLightingModel.HemisphericLight.SetLightColor(DirectX::XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f));
	SLightingModel.HemisphericLight.SetAmbientDown(DirectX::XMFLOAT3A(0.3f, 0.3f, 0.3f));
	SLightingModel.HemisphericLight.SetAmbientRange(DirectX::XMFLOAT3A(0.3f, 0.3f, 0.3f));

	// Directional light
	SLightingModel.DirectionalLight.SetLightColor(DirectX::XMFLOAT4(1.f, 1.f, 1.f, 1.0f));
	SLightingModel.DirectionalLight.SetLightDirection(DirectX::XMFLOAT4(0.f, 0.0f, -1.0f, 0.0f));
	
	// Initializing ambience
	SSkyBox.CreateSkyBox(&SRenderer, &SCamera);
	SGrid.CreateGrid(20, 20, 20, 20, SRenderer, SCamera);
}

// EVENT TICK
static void EventTick()
{
	SRenderer.RenderFrame(&RenderFrame, 0.03f, 0.03f, 0.03f, 1.f);
}

// All objects are rendered in this callback function...
static void RenderFrame(void)
{
	SGrid.DrawGrid();
	SSkyBox.Render();

	// Draw Wireframe and vertex overlay for selected mesh(s)...
	for (int i = 0; i < vSelectedMeshID.size(); i++)
	{
		UpdateWireframeShaderCB(vSelectedMeshID[i]);

		SRenderer.UseShader(&vWireframeShaderString[vSelectedMeshID[i]], sizeof(Vertex), 0, D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

		SRenderer.BindConstatntBuffer(0, 1, &vWireframeShaderString[vSelectedMeshID[i]].GetCB1());
		SRenderer.BindConstatntBuffer(1, 1, &vWireframeShaderString[vSelectedMeshID[i]].GetCB2());

		// Drawing the vertices...
		SRenderer.GetDeviceContext()->RSSetState(SRenderer.GetRasterizerState());
		SRenderer.GetDeviceContext()->DrawIndexed(vMeshString[vSelectedMeshID[i]].GetIndicesCount(), 0, 0);
		
		//Draw Vertex overlay if VertexModeID is not -1...
		if (VertexModelID == vSelectedMeshID[i])
		{
			UpdateVeretxOverlayShaderCB(VertexModelID);

			SRenderer.BindConstatntBuffer(0, 1, &vVertexShaderString[VertexModelID].GetCB1());
			SRenderer.BindConstatntBuffer(1, 1, &vVertexShaderString[VertexModelID].GetCB2());
			SRenderer.UseShader(&vVertexShaderString[VertexModelID], sizeof(Vertex), 0, D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);

			SRenderer.GetDeviceContext()->RSSetState(SRenderer.GetRasterizerState());
			SRenderer.GetDeviceContext()->DrawIndexed(vMeshString[VertexModelID].GetIndicesCount(), 0, 0);
		}

		//Draw Face overlay if FaceModeID is not -1...
		if (vSelectedMeshID[i] == FaceModelID)
		{
			UpdateFaceShaderCB(i);

			// Draw mesh string with default solid shader...
			SRenderer.UseShader(&vFaceShaderString[i], sizeof(Vertex), 0, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

			SRenderer.BindConstatntBuffer(0, 1, &vFaceShaderString[i].GetCB1());
			SRenderer.BindConstatntBuffer(1, 1, &vFaceShaderString[i].GetCB2());

			// Drawing the vertices...
			SRenderer.GetDeviceContext()->RSSetState(SRenderer.GetRasterizerState());
			SRenderer.GetDeviceContext()->Draw(vFaceOverlayMesh.size(), 0);
		}
	}

	for (int i = 0; i < vMeshString.size(); i++)
	{
		UpdateSolidShaderCB(i);

		// Draw mesh string with default solid shader...
		SRenderer.UseShader(&vSolidShaderString[i], sizeof(Vertex), 0, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		SRenderer.BindConstatntBuffer(0, 1, &vSolidShaderString[i].GetCB1());
		SRenderer.BindConstatntBuffer(1, 1, &vSolidShaderString[i].GetCB2());

		// Drawing the vertices...
		SRenderer.GetDeviceContext()->RSSetState(SRenderer.GetRasterizerState());
		SRenderer.GetDeviceContext()->DrawIndexed(vMeshString[i].GetIndicesCount(), 0, 0);
	}

	SGUI.RenederGUI(&DrawGUI);
}

static void MouseCallback(EventType EType)
{
	switch (EType)
	{
		case EventType::MOUSE_PRESSED:
			SWindow.GetDeltaMousePosition();
			if (SWindow.GetMouse()[MOUSE1] && !SGUI.IsOver())
			{
				if (vMeshString.size())
				{
					DirectX::XMMATRIX mP = SCamera.GetProjectionMatrix();
					DirectX::XMMATRIX vP = SCamera.GetViewMatrix();

					// Project all the verts onto a 2D plane...
					SProjector.ProjectVerts(&vMeshString[0],
						vMeshString.size() * sizeof(CMesh),
						&vP,
						&mP,
						vProjectedMeshString);

					if (VertexModelID != -1) PickVertex();
					else if (FaceModelID != -1) PickFace();
					else PickObject();
				}
			}
			break;

		case EventType::MOUSE_RELEASED:
			SWindow.GetDeltaMousePosition();
			break;

		case EventType::MOUSE_WHEEL_UP:
			break;

		case EventType::MOUSE_WHEEL_DOWN:
			break;

		case EventType::MOUSE_MOVE:
		{
			SProjector.vertsUpdated = false;

			if (SWindow.GetMouse()[MOUSE1] && SWindow.GetMouse()[MOUSE2])
			{
				POINT DeltaPos = SWindow.GetDeltaMousePosition();
				SCamera.Move(DeltaPos.x, DeltaPos.y, 0.f);
				SLightingModel.DirectionalLight.AttachToCamera(SCamera.GetCamerPosition());
				SLightingModel.DirectionalLight.AttachToCamera(DirectX::XMVectorScale(SCamera.GetForwardVector(), -1.f));
				SGUI.UpdateGUIScaling();
			}
			else if (SWindow.GetMouse()[MOUSE2])
			{
				POINT DeltaPos = SWindow.GetDeltaMousePosition();
				SCamera.AddPitch(DeltaPos.y);
				SCamera.AddYaw(DeltaPos.x);
				SLightingModel.DirectionalLight.AttachToCamera(SCamera.GetCamerPosition());
				SLightingModel.DirectionalLight.AttachToCamera(DirectX::XMVectorScale(SCamera.GetForwardVector(), -1.f));
			}
		}
			break;
	}
}
static void KeyCallback(EventType EType)
{
	switch (EType)
	{
	SWindow.UpdateDeltaTime();
	case EventType::KEY_PRESSED:
	{
		if (SWindow.GetKeys()[KEY_W] && SWindow.GetMouse()[MOUSE2])
		{
			SLightingModel.DirectionalLight.AttachToCamera(DirectX::XMVectorScale(SCamera.GetForwardVector(), -1.f));
			SCamera.MoveForward(SWindow.GetDeltaTime());
			SProjector.vertsUpdated = false;
		}
		if (SWindow.GetKeys()[KEY_S] && SWindow.GetMouse()[MOUSE2])
		{
			SLightingModel.DirectionalLight.AttachToCamera(DirectX::XMVectorScale(SCamera.GetForwardVector(), -1.f));
			SCamera.MoveBackward(SWindow.GetDeltaTime());
			SProjector.vertsUpdated = false;
		}
		if (SWindow.GetKeys()[KEY_D] && SWindow.GetMouse()[MOUSE2])
		{
			SLightingModel.DirectionalLight.AttachToCamera(DirectX::XMVectorScale(SCamera.GetForwardVector(), -1.f));
			SCamera.MoveRight(SWindow.GetDeltaTime());
			SProjector.vertsUpdated = false;
		}
		if (SWindow.GetKeys()[KEY_A] && SWindow.GetMouse()[MOUSE2])
		{
			SLightingModel.DirectionalLight.AttachToCamera(DirectX::XMVectorScale(SCamera.GetForwardVector(), -1.f));
			SCamera.MoveLeft(SWindow.GetDeltaTime());
			SProjector.vertsUpdated = false;
		}
		if (SWindow.GetKeys()[KEY_ESCAPE] && SWindow.GetMouse()[MOUSE2])
		{
			exit(0);
		}

	}
		break;
	case EventType::KEY_RELEASED:
		break;
	}
}
static void WindowCallback(EventType EType)
{
	switch (EType)
	{
		case EventType::WINDOW_RESIZE:
		{
			SCamera.UpdateContextRect(SWindow.GetWindowWidth(), SWindow.GetWindowHeight());
		}
			break;
		case EventType::WINDOW_DESTROY:
			exit(0);
			break;
	}
}
static void GizmoCallback(DirectX::XMMATRIX m)
{
	using namespace DirectX;
	if (vSelectedVerticesID.size())
	{
		for (int i = 0; i < vSelectedVerticesID.size(); i++)
		{
			vMeshString[VertexModelID].GetVertices()[vSelectedVerticesID[i]].Transform(m);
		}
		vSolidShaderString[VertexModelID].UpdateVertex(vMeshString[VertexModelID].GetVertices(), vMeshString[VertexModelID].GetVerticesSize());
		vWireframeShaderString[VertexModelID].UpdateVertex(vMeshString[VertexModelID].GetVertices(), vMeshString[VertexModelID].GetVerticesSize());
		vVertexShaderString[VertexModelID].UpdateVertex(vMeshString[VertexModelID].GetVertices(), vMeshString[VertexModelID].GetVerticesSize());
	}
	else if (vSelectedFacesID.size())
	{
		for (int i = 0; i < vFaceOverlayMesh.size(); i++)
		{
			if(i < vSelectedFacesID.size())vMeshString[FaceModelID].GetVertices()[vSelectedFacesID[i]].Transform(m);
			vFaceOverlayMesh[i].Transform(m);
		}
		vSolidShaderString[FaceModelID].UpdateVertex(vMeshString[FaceModelID].GetVertices(), vMeshString[FaceModelID].GetVerticesSize());
		vFaceShaderString[FaceModelID].UpdateVertex(&vFaceOverlayMesh[0], vFaceOverlayMesh.size() * sizeof(Vertex));
		vWireframeShaderString[FaceModelID].UpdateVertex(vMeshString[FaceModelID].GetVertices(), vMeshString[FaceModelID].GetVerticesSize());
		vVertexShaderString[FaceModelID].UpdateVertex(vMeshString[FaceModelID].GetVertices(), vMeshString[FaceModelID].GetVerticesSize());
	}
	else if (FaceModelID == -1 && VertexModelID == -1)
	{
		for (int i = 0; i < vSelectedMeshID.size(); i++)
		{
			vMeshString[vSelectedMeshID[i]].SetModelMatrix(vMeshString[vSelectedMeshID[i]].GetModelMatrix() * m);
		}
	}
}
void UpdateSolidShaderCB(unsigned int i)
{
	using namespace DirectX;
	CB_SolidTick cb;
		cb.mWorld = XMMatrixTranspose(vMeshString[i].GetModelMatrix());
		cb.mView = XMMatrixTranspose(SCamera.GetViewMatrix());
		cb.vLightColor = SLightingModel.DirectionalLight.GetLightColor();
		cb.vLightDirection = SLightingModel.DirectionalLight.GetLightDirection();
	vSolidShaderString[i].UpdateCB1(&cb);
}
void UpdateWireframeShaderCB(unsigned int i)
{
	CB_WireframeTick cb;
		cb.mWorld = XMMatrixTranspose(vMeshString[i].GetModelMatrix());
		cb.mView = XMMatrixTranspose(SCamera.GetViewMatrix());
	vWireframeShaderString[i].UpdateCB1(&cb);
	
	CB_WireframeOnEvent ecb;
		ecb.mProjection = XMMatrixTranspose(SCamera.GetProjectionMatrix());
	vWireframeShaderString[i].UpdateCB2(&ecb);
}
void UpdateVeretxOverlayShaderCB(unsigned int i)
{
	CB_VertexTick cb;
		cb.mWorld = XMMatrixTranspose(vMeshString[i].GetModelMatrix());
		cb.mView = XMMatrixTranspose(SCamera.GetViewMatrix());
	vVertexShaderString[i].UpdateCB1(&cb);

	CB_VertexOnEvent ecb;
		ecb.mProjection = XMMatrixTranspose(SCamera.GetProjectionMatrix());
	vVertexShaderString[i].UpdateCB2(&ecb);
	
}

void UpdateFaceShaderCB(unsigned int i)
{
	CB_SolidTick cb;
		cb.mWorld = XMMatrixTranspose(vMeshString[i].GetModelMatrix());
		cb.mView = XMMatrixTranspose(SCamera.GetViewMatrix());
		cb.vLightColor = SLightingModel.DirectionalLight.GetLightColor();
		cb.vLightDirection = SLightingModel.DirectionalLight.GetLightDirection();
	vFaceShaderString[i].UpdateCB1(&cb);
}

// called on mouse down
static void PickObject()
{
	// Clear the selected mesh array...
	if (!SWindow.GetKeys()[KEY_SHIFT]) vSelectedMeshID.clear();

	// Get mouse coordinates in cartisian-coords...
	float2 Mouse = MouseInCartisian(*SWindow.GetHWindow(), SWindow.GetWindowWidth(), SWindow.GetWindowHeight());

	// Itrerate over the meshes to check intersections...
	for (int i = 0; i < vProjectedMeshString.size(); i++)
	{
		// iterate over each triangle-primitive...
		for (int j = 0; j < vMeshString[i].GetIndicesCount() - 3; j += 3)
		{
			// check intersection...
			if (SProjector.InsideTri(
				vProjectedMeshString[i].verts[vMeshString[i].GetIndices()[j]].m128_f32[0],
				vProjectedMeshString[i].verts[vMeshString[i].GetIndices()[j]].m128_f32[1],
				vProjectedMeshString[i].verts[vMeshString[i].GetIndices()[j + 1]].m128_f32[0],
				vProjectedMeshString[i].verts[vMeshString[i].GetIndices()[j + 1]].m128_f32[1],
				vProjectedMeshString[i].verts[vMeshString[i].GetIndices()[j + 2]].m128_f32[0],
				vProjectedMeshString[i].verts[vMeshString[i].GetIndices()[j + 2]].m128_f32[1],
				Mouse.x,
				Mouse.y))
			{
				// only select if it hasn't been selected yet...
				if (vSelectedMeshID.empty())
				{
					SGUI.ShowGizmo(true, vMeshString[i].GetGizmoMatrix());
					vSelectedMeshID.push_back(i);
				}
				else if (UniqueiItem<short>(&vSelectedMeshID[0], vSelectedMeshID.size(), i))
				{
					vSelectedMeshID.push_back(i); // add this mesh to selected index...
				}
				break;
			}
		}
	}
	if (vSelectedMeshID.size() < 1) SGUI.ShowGizmo(false);
}

static void PickVertex()
{
	// Clear the selected vertex array...
	if (!SWindow.GetKeys()[KEY_SHIFT])
	{
		for (int i = 0; i < vSelectedVerticesID.size(); i++)
		{
			vMeshString[VertexModelID].GetVertices()[vSelectedVerticesID[i]].u = 0;
		}
		vSelectedVerticesID.clear();
	}

	// Get mouse coordinates in cartisian-coords...
	float2 Mouse = MouseInCartisian(*SWindow.GetHWindow(), SWindow.GetWindowWidth(), SWindow.GetWindowHeight());

	//..
	std::vector<unsigned short> vSelectedVertsT;

	// Iterate over all vertices of the selected mesh...
	for (int i = 0; i < vMeshString[VertexModelID].GetIndicesCount(); i++)
	{
		if (nearlyEqual<float>(vProjectedMeshString[VertexModelID].verts[vMeshString[VertexModelID].GetIndices()[i]].m128_f32[0], Mouse.x, 0.02) &&
			nearlyEqual<float>(vProjectedMeshString[VertexModelID].verts[vMeshString[VertexModelID].GetIndices()[i]].m128_f32[1], Mouse.y, 0.02))
		{
			vSelectedVerticesID.push_back(vMeshString[VertexModelID].GetIndices()[i]);
			vMeshString[VertexModelID].GetVertices()[vMeshString[VertexModelID].GetIndices()[i]].u = 1;
		}
	}

	// computing the average (position) of all selected vertices...
	float x = 0;
	float y = 0;
	float z = 0;
	for (int j = 0; j < vSelectedVerticesID.size(); j++)
	{
		x += vMeshString[VertexModelID].GetVertices()[vSelectedVerticesID[j]].x;
		y += vMeshString[VertexModelID].GetVertices()[vSelectedVerticesID[j]].y;
		z += vMeshString[VertexModelID].GetVertices()[vSelectedVerticesID[j]].z;
		
	}
	x /= vSelectedVerticesID.size();
	y /= vSelectedVerticesID.size();
	z /= vSelectedVerticesID.size();
	SGUI.SetGizmoPosition(x, y, z);
	vVertexShaderString[VertexModelID].UpdateVertex(vMeshString[VertexModelID].GetVertices(), vMeshString[VertexModelID].GetVerticesSize());
}

static void PickFace()
{
	// Clear the selected tri array...
	if (!SWindow.GetKeys()[KEY_SHIFT])
	{
		vFaceOverlayMesh.clear();
		vSelectedFacesID.clear();
	}

	// Get mouse coordinates in cartisian-coords...
	float2 Mouse = MouseInCartisian(*SWindow.GetHWindow(), SWindow.GetWindowWidth(), SWindow.GetWindowHeight());
	std::vector<Vertex>	vFaceOverlayTC;

	// iterate over each triangle-primitive...
	for (int j = 0; j < vMeshString[FaceModelID].GetIndicesCount() - 3; j += 3)
	{
		// check intersection...
		if (SProjector.InsideTri(
			vProjectedMeshString[FaceModelID].verts[vMeshString[FaceModelID].GetIndices()[j]].m128_f32[0],
			vProjectedMeshString[FaceModelID].verts[vMeshString[FaceModelID].GetIndices()[j]].m128_f32[1],
			vProjectedMeshString[FaceModelID].verts[vMeshString[FaceModelID].GetIndices()[j + 1]].m128_f32[0],
			vProjectedMeshString[FaceModelID].verts[vMeshString[FaceModelID].GetIndices()[j + 1]].m128_f32[1],
			vProjectedMeshString[FaceModelID].verts[vMeshString[FaceModelID].GetIndices()[j + 2]].m128_f32[0],
			vProjectedMeshString[FaceModelID].verts[vMeshString[FaceModelID].GetIndices()[j + 2]].m128_f32[1],
			Mouse.x,
			Mouse.y))
		{
			for (int i = 0, c = 0; i < 3; i++, c++)
			{
				bool rept = false;
				for (int m = 0; m < vSelectedFacesID.size(); m++)
				{
					if (vMeshString[FaceModelID].GetIndices()[j + c] == vSelectedFacesID[m])
					{
						rept = true;
						break;
					}
				}
				if (!rept)
				{
					vSelectedFacesID.push_back(vMeshString[FaceModelID].GetIndices()[j + c]);
				}
				vFaceOverlayTC.push_back(vMeshString[FaceModelID].GetVertices()[vMeshString[FaceModelID].GetIndices()[j + c]]);
			}
		}
	}
	if (vFaceOverlayTC.size())
	{
		for (int i = 0; i < vFaceOverlayTC.size(); i++)
		{
			vFaceOverlayMesh.push_back(vFaceOverlayTC[i]);
		}
		vFaceShaderString[FaceModelID].UpdateVertex(&vFaceOverlayMesh[0], vFaceOverlayMesh.size() * sizeof(Vertex));
	}
	{
		float x = 0;
		float y = 0;
		float z = 0;
		for (int i = 0; i < vFaceOverlayMesh.size(); i++)
		{

			x += vFaceOverlayMesh[i].x;
			y += vFaceOverlayMesh[i].y;
			z += vFaceOverlayMesh[i].z;
		}
		x /= vFaceOverlayMesh.size();
		y /= vFaceOverlayMesh.size();
		z /= vFaceOverlayMesh.size();
		SGUI.SetGizmoPosition(x, y, z);
	}
}