#pragma once
// Classes
#include "Window.h"
#include "Renderer.h"
#include "Mesh.h"
#include "Shader.h"
#include "SolidShader.h"
#include "WireframeShader.h"
#include "VertexOverlayShader.h"
#include "CCamera.h"
#include "CLight.h"
#include "CGUI.h"
#include "ModelLoader.h"
#include "SkyBox.h"
#include "Projector.h"
#include "Grid.h"

// D3d libraries ( static )
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx11.lib")
#pragma comment (lib, "d3dx10.lib")
#pragma comment (lib, "assimp.lib")

#ifdef max
#undef max
#endif

#ifdef min
#undef min
#endif


// Global declarations
static CWindow			SWindow;
static CRenderer		SRenderer;
static CCamera			SCamera;
static CLightingModel	SLightingModel;
CGUI					SGUI(SCamera);
static CSkyBox			SSkyBox;
static Projector		SProjector;
static CGrid			SGrid;

// These objects are used across multiple translation units...
ModelLoader									SLoader;
std::vector<CMesh>							vMeshString;
static std::vector<SProjectedMesh>			vProjectedMeshString;
static std::vector<CSolidShader>			vSolidShaderString;		// array of solid shaders
static std::vector<CWireframeShader>		vWireframeShaderString;	// array of shaders to draw a wireframe overlay on selected meshe(s)
static std::vector<CVertexOverlayShader> 	vVertexShaderString;	// ^^ a vertex overlay [not to be confused with a vertex shader]
static std::vector<CSolidShader> 			vFaceShaderString;		// ^^ a face overlay shader arrary
static std::vector<Vertex>					vFaceOverlayMesh;		//
static std::vector<short>					vSelectedVerticesID;	// selected vertices of selected mesh
static std::vector<short>					vSelectedFacesID;		// selected vertices of selected mesh
std::vector<short>							vSelectedMeshID;		// selected meshes in vMeshString

short						VertexModelID = -1;		// ID of the model which is being edited in vertex mode...
short						FaceModelID = -1;		// ID of the model which is being edited in face mode...

void UpdateShaderString();
