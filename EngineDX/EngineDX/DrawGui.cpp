#pragma once
#include "pch.h"
#include "drawgui.h"
#include "SolidShader.h"
#include "CGUI.h"
#include "ModelLoader.h"


// external objects decleared in main.h
extern ModelLoader							SLoader;
extern CGUI									SGUI;
extern std::vector<CMesh>					vMeshString;
extern std::vector<short>					vSelectedMeshID;
extern short								VertexModelID;
extern short								FaceModelID;
extern void UpdateShaderString();



static std::string dir = "C:\\*";
static size_t find_in_Str(const char* str, const char* to_find, size_t str_size, size_t size)
{
	for (int i = 0; i < str_size - size; i++)
		if(memcmp(&str[i], to_find, size - 1) == 0) return i;
	return -1;
}
static int IsExt(std::string str, const char* ext)
{
	size_t ext_p = find_in_Str(str.c_str(), ".", str.size(), sizeof("."));
	if (ext_p != -1)
	{
		if (str.substr(ext_p, (str.size() - ext_p)) == ext)
			return 1;
	}
	else return 0;
	return -1;
}

void DrawGUI()
{
	MainMenu();
}

void MainMenu()
{
	static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None | ImGuiDockNodeFlags_PassthruCentralNode;
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_DockNodeHost;
	ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->Pos);
	ImGui::SetNextWindowSize(viewport->Size);
	ImGui::SetNextWindowViewport(viewport->ID);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
	window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
	window_flags |= ImGuiWindowFlags_NoBackground;

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::Begin("DockSpace", nullptr, window_flags);
	ImGui::PopStyleVar();
	ImGui::PopStyleVar(2);

	// DockSpace
	ImGuiIO& io = ImGui::GetIO();
	ImGuiID dockspace_id = ImGui::GetID("DockSpace");
	ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
	if (ImGui::BeginMainMenuBar())
	{
		FileMenu();
		EditMenu();
	}

	// DockSpace
	ImGui::EndMainMenuBar();

		//DirectoryPane();
		PropertiesPane();
		Toolbox();

	ImGui::End();
}

void FileMenu()
{
	if (ImGui::BeginMenu("File"))
	{
		if (ImGui::MenuItem("SampleModel"))
		{
			SLoader.LoadModel("teapot.obj", &vMeshString);
			UpdateShaderString();
		}
	
		ImGui::EndMenu();
	}

}
void EditMenu()
{
	if (ImGui::BeginMenu("Edit"))
	{
	}
}

static int b_size = 50;
static bool anything = false;
static WIN32_FIND_DATA w_data;
static HANDLE* hFind;
//void DirectoryPane()
//{
//	hFind = new HANDLE;
//	ImGui::Begin("Project Directory");
//	ImGui::NewLine();
//	//
//	//{
//	//	ImGui::Begin("Drives");
//
//	//	char* drive = new char[130];
//	//	GetLogicalDriveStrings(130, drive);
//
//	//	for (int i = 0; i < 130; i += 4)
//	//	{
//	//		if (char(drive[i]) == -52 || char(drive[i]) == 0)
//	//			break;
//	//		else
//	//		{
//	//			if (ImGui::Button(&drive[i], ImVec2(ImGui::GetWindowWidth() - 15, 20)))
//	//			{
//	//				dir = &drive[i];
//	//				dir += "\*";
//	//			}
//	//		}
//	//	}
//	//	ImGui::End();
//	//	if (drive) delete[130] drive;
//	//}
//	if(ImGui::Button("Back", ImVec2(100, 20)))
//	{
//		if (dir.length() > 5)
//		{
//			dir = dir.substr(0, dir.length() - 3);
//			dir = dir.substr(0, dir.find("\\", sizeof("\\")) + 1) + "*";
//		}
//		else dir = "";
//	}
//	ImGui::SameLine();
//	ImGui::SliderInt("Grid", &b_size, 50, 100, "%d");
//	
//	if ((*hFind = FindFirstFile(dir.c_str(), &w_data)) != INVALID_HANDLE_VALUE)
//	{
//		while (FindNextFile(*hFind, &w_data) != 0)
//			if (IsExt(w_data.cFileName, ".obj") > -1 || IsExt(w_data.cFileName, ".fbx") > -1)
//			{
//				if (ImGui::GetWindowWidth() > 77 && b_size > 0)
//				{
//					ImGui::Columns(ImGui::GetWindowWidth() / b_size);
//					{
//						if (ImGui::Button(std::string(w_data.cFileName).c_str(), ImVec2(b_size - 13, b_size - 13)))
//						{
//							if (IsExt(w_data.cFileName, ".obj") || IsExt(w_data.cFileName, ".fbx"))
//							{
//								SLoader.LoadModel(w_data.cFileName, &vMeshString);
//								UpdateShaderString();
//							}
//							else
//							{
//								dir = dir.substr(0, dir.length() - 1);
//								dir.append(w_data.cFileName);
//								dir.append("\\*");
//							}
//						}
//						ImGui::TextWrapped(w_data.cFileName);
//						ImGui::NextColumn();
//					}
//				}
//			}
//	}
//	delete[] hFind;
//	ImGui::End();
//	
//}

void PropertiesPane()
{
	ImGui::Begin("Properties");
	for (int i = 0; i < vSelectedMeshID.size(); i++)
	{
		if (ImGui::CollapsingHeader("Details"))
		{
			if (ImGui::TreeNode("Primitives"))
			{
				ImGui::Text("Vertices: %d", vMeshString[vSelectedMeshID[i]].GetVerticesCount());
				ImGui::Text("Triangles: %d", vMeshString[vSelectedMeshID[i]].GetIndicesCount() / 3);
				ImGui::Text("Indices: %d", vMeshString[vSelectedMeshID[i]].GetIndicesCount());
				ImGui::TreePop();
			}
		}
		if (ImGui::CollapsingHeader("Transform"))
		{
			if (ImGui::TreeNode("Translate"))
			{
				// X translation DragFloat
				ImGui::DragFloat("X",
					(float*)&vMeshString[vSelectedMeshID[i]].GetModelMatrix().r[3].m128_f32[0],
					0.3f,
					(float)vMeshString[vSelectedMeshID[i]].GetModelMatrix().r[3].m128_f32[0] - 100.f,
					(float)vMeshString[vSelectedMeshID[i]].GetModelMatrix().r[3].m128_f32[0] + 100.f,
					"%.3f",
					1.0f);

				// Y translation DragFloat
				vMeshString[vSelectedMeshID[i]].GetModelMatrix();
				ImGui::DragFloat("Y",
					(float*)&vMeshString[vSelectedMeshID[i]].GetModelMatrix().r[3].m128_f32[1],
					0.3f,
					(float)vMeshString[vSelectedMeshID[i]].GetModelMatrix().r[3].m128_f32[1] - 100.f,
					(float)vMeshString[vSelectedMeshID[i]].GetModelMatrix().r[3].m128_f32[1] + 100.f,
					"%.3f",
					1.0f);

				// Z translation DragFloat
				vMeshString[vSelectedMeshID[i]].GetModelMatrix();
				ImGui::DragFloat("Z",
					(float*)&vMeshString[vSelectedMeshID[i]].GetModelMatrix().r[3].m128_f32[2],
					0.3f,
					(float)vMeshString[vSelectedMeshID[i]].GetModelMatrix().r[3].m128_f32[2] - 100.f,
					(float)vMeshString[vSelectedMeshID[i]].GetModelMatrix().r[3].m128_f32[2] + 100.f,
					"%.3f",
					1.0f);

				ImGui::TreePop();
			}
			if (ImGui::TreeNode("Rotate"))
			{
				ImGui::TreePop();
			}
			if (ImGui::TreeNode("Scale"))
			{
				ImGui::TreePop();
			}
		}
		if (ImGui::CollapsingHeader("Edit Primitives"))
		{
			if (ImGui::Button("Edit Vertices", ImVec2(ImGui::GetWindowWidth(), 25)))
			{
				VertexModelID != vSelectedMeshID[i] ? VertexModelID = vSelectedMeshID[i] : VertexModelID = -1;
			}
			if(ImGui::Button("Edit Triangles", ImVec2(ImGui::GetWindowWidth(), 25)))
			{
				FaceModelID != vSelectedMeshID[i] ? FaceModelID = vSelectedMeshID[i] : FaceModelID = -1;
			}
		}
		break;
	}
	ImGui::End();
}

void Toolbox()
{
	ImGui::Begin("Toolbox prototype");
	if (ImGui::Button("T", ImVec2(31, 31)))
	{
		SGUI.GizmoTranslate();
	}
	ImGui::SameLine();
	if (ImGui::Button("R", ImVec2(31, 31)))
	{
		SGUI.GizmoRotate();
	}
	ImGui::SameLine();
	if (ImGui::Button("S", ImVec2(31, 31)))
	{
		SGUI.GizmoScale();
	}
	ImGui::End();
}
