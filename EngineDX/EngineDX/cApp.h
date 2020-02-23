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


class cApp
{
private:
	// imports models using assimps
	ModelLoader cLoader;

	// Main array of meshes in the scene
	std::vector<CMesh> vMeshString;

	// vMeshString projected on a 2d surface
	std::vector<SProjectedMesh>	vProjectedMeshString;

	// the main shader string with which all the models are rendered
	// one shader for each mesh
	std::vector<CSolidShader> vSolidShaderString;

	// shader array with which the wireframe overlay is drawn
	// one shader for each mesh
	std::vector<CWireframeShader> vWireframeShaderString;

	// the shader string with which the vertex overlay is rendered
	// one shader for each mesh
	std::vector<CVertexOverlayShader> vVertexShaderString;

	// shader to render the overlay for selected faces (vFaceOverlayMesh)
	CSolidShader vFaceShaderString;

	// verts of the selected faces
	std::vector<Vertex> vFaceOverlayMesh;

	// IDs of the selected meshes
	std::vector<short>							vSelectedMeshID;

	// IDs of the verts that are to be transformed on gizmo callback
	std::vector<short>							vSelectedVerticesID;

	// vertex IDs for the faces that have to be transformed on gizmo callback
	std::vector<short>							vSelectedFacesID;



	// Global declarations
	CWindow			cWindow;
	CRenderer		cRenderer;
	CCamera			cCamera;
	CLightingModel	cLightingModel;
	CGUI			cGUI;
	CSkyBox			cSkyBox;
	Projector		cProjector;
	CGrid			cGrid;


	short						VertexModelID = -1;		// ID of the model which is being edited in vertex mode...
	short						FaceModelID = -1;		// ID of the model which is being edited in face mode...

	void UpdateShaderString();

public:
	cApp();
	~cApp();
};

