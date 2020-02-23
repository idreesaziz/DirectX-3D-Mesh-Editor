#include "pch.h"
#include "CGUI.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

CGUI::CGUI(CCamera & c)
	:
camera(&c)
{
}

void CGUI::Manipulate(const DirectX::XMMATRIX *view,
					  const DirectX::XMMATRIX *projection,
					  DirectX::XMMATRIX *matrix,
					  DirectX::XMMATRIX *deltaMatrix,
					  float *snap,
					  float *localBounds,
					  float *boundsSnap)
{
	ImGuizmo::Manipulate((const float*)view, (const float*)projection, mCurrentGizmoOperation, mCurrentGizmoMode, (float*)matrix, (float*)deltaMatrix, snap, localBounds, boundsSnap);
}

CGUI::CGUI()
{
}

void CGUI::InitGUI(class CRenderer* pRenderer, HWND& hWnd, void(*gizmoCallback)(DirectX::XMMATRIX deltaMatrix))
{
	if (hWnd)this->hWnd = &hWnd;
	if (pRenderer)this->pRenderer = pRenderer;
	GizmoCallback = gizmoCallback;
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	*io = ImGui::GetIO(); (void)io;
	io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
	io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
	io->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
	ImGuiStyle& style = ImGui::GetStyle();
	if (io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}
	// Setup Platform/Renderer bindings
	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX11_Init(pRenderer->GetDevice(), pRenderer->GetDeviceContext());
	
	// Load Fonts
	// - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
	// - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
	// - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
	// - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
	// - Read 'misc/fonts/README.txt' for more instructions and details.
	// - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
	//io->Fonts->AddFontDefault();
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
	//io->Fonts->AddFontFromFileTTF("../../misc/fonts/ProggyTiny.ttf", 10.0f);
	ImFont* font = io->Fonts->AddFontFromFileTTF("Fonts//Calibrib.ttf", 14.0f, NULL, io->Fonts->GetGlyphRangesJapanese());
	//if (!font) MessageBox(nullptr, "", "Error", 0);
	//IM_ASSERT(font != NULL);

	mCurrentGizmoOperation = ImGuizmo::OPERATION(ImGuizmo::TRANSLATE);
	mCurrentGizmoMode = ImGuizmo::MODE(ImGuizmo::LOCAL);
}
void CGUI::RenederGUI(void(*DrawGui)(void))
{
	// Start Dear ImGui frame
	ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	ImGuizmo::BeginFrame();
	
	if (Gizmo)
	{
		ImGuiIO& gio = ImGui::GetIO();
		ImGuizmo::SetRect(0, 0, gio.DisplaySize.x, gio.DisplaySize.y);
		Manipulate(&camera->GetViewMatrix(), &camera->GetProjectionMatrix(), &GizmoMatrix, &DeltaMatrix, NULL, NULL, NULL);
		if (!D3DXMatrixIsIdentity((D3DXMATRIX*)&DeltaMatrix)) GizmoCallback(DeltaMatrix);
	}
		if (DrawGui)DrawGui();
		//if (DrawGui)t_rGUI = std::thread(DrawGui);
		//t_rGUI.join();

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	// Update and Render additional Platform Windows
	if (io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
	}
}

void CGUI::UpdateGUIScaling()
{
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void CGUI::Shutdown()
{
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
	delete[] io;
}

void CGUI::Restart()
{
	//Shutdown();
	//HWND h;
	//ZeroMemory(h, 10);
}

void CGUI::ShowGizmo(bool show, DirectX::XMMATRIX GizmoMat)
{
	Gizmo = show;
	if (show)
	{
		GizmoMatrix = GizmoMat;
	}
}

void CGUI::ShowGizmo(bool show)
{
	Gizmo = show;
}

void CGUI::GizmoTranslate()
{
	mCurrentGizmoOperation = ImGuizmo::OPERATION(ImGuizmo::TRANSLATE);
}

void CGUI::GizmoRotate()
{
	mCurrentGizmoOperation = ImGuizmo::OPERATION(ImGuizmo::ROTATE);
}

void CGUI::GizmoScale()
{
	mCurrentGizmoOperation = ImGuizmo::OPERATION(ImGuizmo::SCALE);
}

void CGUI::UpdateGuizmo()
{
	GizmoMatrix *= DeltaMatrix;
}

void CGUI::SetGizmoPosition(float x, float y, float z)
{
	DirectX::XMMATRIX m = DirectX::XMMatrixIdentity();
	m.r[3].m128_f32[0] = x;
	m.r[3].m128_f32[1] = y;
	m.r[3].m128_f32[2] = z;
	GizmoMatrix = m;
	int i = 0;
}

ImGuiIO CGUI::GetIO()
{
	return ImGui::GetIO();
}

bool CGUI::IsOver()
{
	return (ImGui::IsAnyItemHovered() + ImGuizmo::IsOver() == 0)? false : true;
}

CGUI::~CGUI()
{
}
