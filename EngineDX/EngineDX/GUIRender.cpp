#include "pch.h"
//#include "CGUI.h"
//#include "Window.h"
//#include "ModelLoader.h"
//
//// all gui rendering is done in this cpp
//static void DrawMainMenu();
//static void DrawFileMenu();
//static void DrawEditMenu();
//static const char* OpenCdlg();
//static bool is_open_dlg = false;
//static int IsExt(std::string str, const char* ext);
//static size_t find_in_Str(const char* str, const char* to_find, size_t str_size, size_t size);
//static int dirItemCount();
//static bool p_open = false;
//extern ModelLoader SLoader;
//extern std::vector<CMesh> vMeshString;
//extern void TestGUIDraw();
//extern void UpdateShaderString();
//
//void DrawGUI(void)
//{
//	DrawMainMenu();
//	//ImGui::BeginPopupContextWindow("this si a c", 1, true);
//}
//
//void DrawMainMenu()
//{
//	static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None | ImGuiDockNodeFlags_PassthruCentralNode;
//	ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_DockNodeHost;
//	ImGuiViewport* viewport = ImGui::GetMainViewport();
//	ImGui::SetNextWindowPos(viewport->Pos);
//	ImGui::SetNextWindowSize(viewport->Size);
//	ImGui::SetNextWindowViewport(viewport->ID);
//	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
//	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
//	window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
//	window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
//	window_flags |= ImGuiWindowFlags_NoBackground;
//
//	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
//	ImGui::Begin("DockSpace", nullptr, window_flags);
//	ImGui::PopStyleVar();
//	ImGui::PopStyleVar(2);
//	
//	// DockSpace
//	ImGuiIO& io = ImGui::GetIO();
//	ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
//	ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
//	if (ImGui::BeginMainMenuBar())
//	{
//		DrawFileMenu();
//		DrawEditMenu();
//	}
//
//	// DockSpace
//	ImGui::EndMainMenuBar();
//	TestGUIDraw();
//	ImGui::End();
//	OpenCdlg();
//}
//
//void DrawFileMenu()
//{
//	if (ImGui::BeginMenu("File"))
//	{
//		if (ImGui::MenuItem("New"))
//		{
//			
//		}
//		if (ImGui::MenuItem("Open"))
//		{
//			is_open_dlg = 1;
//		}
//		if (ImGui::MenuItem("Save"))
//		{
//
//		}
//
//		if (ImGui::MenuItem("Utah Teapot"))
//		{
//			SLoader.LoadModel("C:\\Users\\Idris\\Downloads\\simplecage.obj", vMeshString);
//			UpdateShaderString();
//		}
//
//		ImGui::EndMenu();
//	}
//}
//
//void DrawEditMenu()
//{
//	if (ImGui::BeginMenu("Edit"))
//	{
//		if (ImGui::MenuItem("Under Development"))
//		{
//
//		}
//		ImGui::EndMenu();
//	}
//}
//
//static char* txt_path = nullptr;
//static std::string pattern = "c:\\*";
//static const char* lastPath;
//static const char* items[1000];
//static int CurItem;
//static std::vector<const char*> DATA;
//static bool initialized = false;
//
//const char* OpenCdlg()
//{
//	if (is_open_dlg)
//	{
//		if (!initialized) 
//		{
//			pattern = "";
//			std::ifstream f;
//			f.open("last_dir.txt", std::ios::in);
//			size_t p = 0;
//			if (f.is_open())
//			{
//				f.seekg(0, std::ios::end);
//				size_t len = f.tellg();
//				txt_path = new char[len - 4];
//				f.seekg(0);
//				f.read(txt_path, sizeof(char) * len);
//				pattern.append(txt_path);
//				delete[] txt_path;
//			}
//			f.close();
//			initialized = true;
//		}
//		ImGui::Begin("Open");
//		{
//			ImGui::BeginChild(1, ImVec2(ImGui::GetWindowWidth() - 20, ImGui::GetWindowHeight() - 85), 1);
//			{
//				WIN32_FIND_DATA w_data;
//				HANDLE hFind;
//				if ((hFind = FindFirstFile(pattern.c_str(), &w_data)) != INVALID_HANDLE_VALUE)
//				{
//					do if (IsExt(w_data.cFileName, ".obj") != -1 || IsExt(w_data.cFileName, ".fbx") != -1)
//					{
//						if (ImGui::Button(w_data.cFileName, ImVec2(200, 30)))
//						{
//							if (IsExt(w_data.cFileName, ".obj") == 1 || IsExt(w_data.cFileName, ".fbx") == 1)
//							{
//								SLoader.LoadModel(pattern.substr(0, pattern.length() - 1).append(("\\%s", w_data.cFileName)), vMeshString);
//								std::ofstream f;
//								f.open("last_dir.txt", std::ios::out);
//								if (f.is_open())
//									f.write(pattern.c_str(), pattern.length());
//								f.close();
//								UpdateShaderString();
//								is_open_dlg = false;
//							}
//							else
//							{
//								pattern = pattern.substr(0, pattern.length() - 1).append(("\\%s", w_data.cFileName));
//								pattern.append("\\*");
//							}
//						}
//					}
//					while (FindNextFile(hFind, &w_data) != 0);
//				}
//
//			}
//			ImGui::EndChild();
//
//			ImGui::SetCursorPos(ImVec2(ImGui::GetWindowWidth() - 170, ImGui::GetWindowHeight() - 35));
//			if ((ImGui::Button("Back", ImVec2(75, 25))))
//			{
//				pattern = pattern.substr(0, pattern.length() - 1);
//				pattern.append("..");
//				pattern.append("\\*");
//			}
//			ImGui::SameLine();
//			if ((ImGui::Button("Cancel", ImVec2(75, 25))))
//			{
//				is_open_dlg = false;
//			}
//
//		}
//		ImGui::End();
//	}
//	return "i'm not sure!";
//}
//
//static int IsExt(std::string str, const char* ext)
//{
//	size_t ext_p = find_in_Str(str.c_str(), ".", str.size(), sizeof("."));
//	if (ext_p != -1)
//	{
//		if (str.substr(ext_p, (str.size() - ext_p)) == ext)
//			return 1;
//	}
//	else return 0;
//	return -1;
//}
//
//static size_t find_in_Str(const char* str, const char* to_find, size_t str_size, size_t size)
//{
//	for (int i = 0; i < str_size - size; i++)
//		if(memcmp(&str[i], to_find, size - 1) == 0) return i;
//	return -1;
//}
//
//static int dirItemCount()
//{
//	WIN32_FIND_DATA data;
//	HANDLE hFind;
//	int i = 0;
//	if ((hFind = FindFirstFile(pattern.c_str(), &data)) != INVALID_HANDLE_VALUE)
//	{
//		do if (IsExt(data.cFileName, ".obj") != -1)
//			i++;
//		while (FindNextFile(hFind, &data) != 0);
//	}
//	return i;
//
//}
