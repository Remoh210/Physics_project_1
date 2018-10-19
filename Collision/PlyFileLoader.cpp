// PlyFileLoader.cpp
#include "globalStuff.h"		// g_pArrayVert and g_pArrayTris

#include <string>
#include <iostream>			// cout, cin, etc. 
#include <fstream>			// fstream 



// Actual variables in memory
// NO extern here
sPlyVertex*		g_pArrayVert = 0;	// = new sPlyTriangle[numberOfTriangles];	// HEAP
unsigned int	g_numberOfVertices = 0;
sPlyTriangle*	g_pArrayTris = 0;	// NULL NULL  nullptr
unsigned int	g_numberOfTriangles = 0;

// Load the file and place it into a temporary 
//	set of arrays (in the CPU's RAM)
bool LoadPlyFileData( std::string fileName )
{
	// Open the file that you asked.
	std::ifstream theFile( fileName.c_str() );	

	// if ( theFile.is_open() == false )
	if ( ! theFile.is_open() )			// More "c" or "C++" ish
	{
		std::cout << "Didn't open file" << std::endl;
		return false;
	}
	
	// file is open OK
	std::string nextData;
	while ( theFile >> nextData )
	{
		if ( nextData == "vertex" ) 
		{
			break;		// exit while loop...
		}
	};
	// ...Jumping down to here

//	unsigned int numberOfVertices = 0;
	theFile >> g_numberOfVertices;

	std::cout << "vertices: " << g_numberOfVertices << std::endl;

	// seach for "face"
	while ( theFile >> nextData )
	{
		if ( nextData == "face" ) 
		{
			break;		// exit while loop...
		}
	};
	// ...Jumping down to here

//	unsigned int numberOfTriangles = 0;
	theFile >> g_numberOfTriangles;
	std::cout << "triangles: " << g_numberOfTriangles << std::endl;

	while ( theFile >> nextData )
	{
		if ( nextData == "end_header" ) 
		{
			break;		// exit while loop...
		}
	};
	// ...Jumping down to here


	g_pArrayVert = new sPlyVertex[g_numberOfVertices];	// HEAP

//	ZeroMemory(); win32
	// C call... (clears memory to all zeros)
	memset( g_pArrayVert, 0, sizeof( sPlyVertex ) * g_numberOfVertices );

	// Read the vertex data into the array
	for ( unsigned int index = 0; index != g_numberOfVertices; index++ )
	{
		theFile >> g_pArrayVert[index].x;
		theFile >> g_pArrayVert[index].y;
		theFile >> g_pArrayVert[index].z;

//		theFile >> g_pArrayVert[index].;
	}

	// Same with triangles

//	sPlyTriangle* pArrayTris = new sPlyTriangle[numberOfTriangles];	// HEAP
	g_pArrayTris = new sPlyTriangle[g_numberOfTriangles];	// HEAP

	memset( g_pArrayTris, 0, sizeof( sPlyTriangle ) * g_numberOfTriangles );

	int TossThisAway = 0;
	for ( unsigned int index = 0; index !=  g_numberOfTriangles; index++ )
	{
		// 3 69 1322 70
		theFile >> TossThisAway;			// 3
		theFile >> g_pArrayTris[index].vertex_index_1;
		theFile >> g_pArrayTris[index].vertex_index_2;
		theFile >> g_pArrayTris[index].vertex_index_3;
	}

	std::cout << "Read from the file OK." << std::endl;

	return true;
}


//void saveLightInfo(std::string filename, std::vector<sLight*> lights)
//{
//	filename = "output/" + filename;
//	std::string line;
//	std::ofstream file(filename.c_str());
//	if (file.is_open())
//	{
//		for (std::vector<sLight*>::iterator it = lights.begin(); it != lights.end(); ++it) 
//		{
//			sLight* CurLight = *it;
//			file << "Position_xyz: " << CurLight->position.x << " " << CurLight->position.y << " " << CurLight->position.z << "\n";
//			file << "Attenuation_xyz: " << CurLight->atten.x << " " << CurLight->atten.y << " " << CurLight->atten.z << "\n";
//			file << "Diffuse_rgbw: " << CurLight->diffuse.x << " " << CurLight->diffuse.y << " " << CurLight->diffuse.z << " " << CurLight->diffuse.w << "\n";
//			file << "on_off: " << CurLight->param2.x << "\n";
//			//pTheOneLight->AtenSphere = false;
//			//LightManager->vecLights.push_back(pTheOneLight);
//			//LightManager->LoadUniformLocations(program);
//		}
//		std::cout << "Lights information saved to " << filename.c_str() << std::endl;
//		file.close();
//	}
//}


void saveLightInfo(std::string filename, std::vector<sLight*> lights)
{
	filename = "output/" + filename;
	std::string line;
	std::ofstream file(filename.c_str());
	if (file.is_open())
	{
		for (std::vector<sLight*>::iterator it = lights.begin(); it != lights.end(); ++it)
		{
			sLight* CurLight = *it;
			file << "Name " << CurLight->lightName << "\n";
			file << "Position_xyz " << CurLight->position.x << " " << CurLight->position.y << " " << CurLight->position.z << "\n";
			file << "Attenuation_xyz " << CurLight->atten.x << " " << CurLight->atten.y << " " << CurLight->atten.z << "\n";
			file << "Diffuse_rgbw " << CurLight->diffuse.x << " " << CurLight->diffuse.y << " " << CurLight->diffuse.z << " " << CurLight->diffuse.w << "\n";
			file << "on_off " << CurLight->param2.x << "\n";
			//pTheOneLight->AtenSphere = false;
			//LightManager->vecLights.push_back(pTheOneLight);
			//LightManager->LoadUniformLocations(program);
		}
		std::cout << "Lights information saved to " << filename.c_str() << std::endl;
		file.close();
	}
}

//Save Models Info to the file
void saveModelInfo(std::string filename, std::vector<cMeshObject*> models)
{
	filename = "output/" + filename;
	std::string line;
	std::ofstream file(filename.c_str());
	if (file.is_open())
	{
		for (std::vector<cMeshObject*>::iterator it = models.begin(); it != models.end(); ++it)
		{
			cMeshObject* CurModel = *it;
			file << "Friendly_Name " << CurModel->friendlyName << "\n";
			file << "Mesh_Name " << CurModel->meshName << "\n";
			file << "Position " << CurModel->position.x << " " << CurModel->position.y << " " << CurModel->position.z << "\n";
			file << "Rotation " << CurModel->postRotation.x << " " << CurModel->postRotation.y << " " << CurModel->postRotation.z << "\n";
			file << "Scale  " << CurModel->nonUniformScale.x << " " << CurModel->nonUniformScale.y << " " << CurModel->nonUniformScale.z << "\n";
			file << "Colour  " << CurModel->objColour.x << " " << CurModel->objColour.y << " " << CurModel->objColour.z << "\n";
			//pTeapot->meshName = "Utah_Teapot_xyz_n.ply";
			//pTeapot->setUniformScale(0.4f);
		}
		std::cout << "Models information saved to " << filename.c_str() << std::endl;
		file.close();
	}
}

//Load models Info from the file




//TXT OUTPUT LOOKS LIKE THIS
//Mesh_Name Utah_Teapot_xyz_n.ply
//Position - 150 60 0
//Rotation - 0.349066 0 0
//Scale 0.1 0.1 0.1
//Colour  0.2 0.8 0.3


void loadModels(std::string filename, std::vector<cMeshObject*> models)
{
	std::ifstream file(("output/" + filename).c_str());

	if (!file.is_open()) { return; }

	std::map<std::string, cMeshObject*> meshObjects;
	for (unsigned int x = 0; x < models.size(); x++)
	{
		std::string friendlyName = models[x]->friendlyName;
		meshObjects[friendlyName] = models[x];
	}

	while (true)
	{
		std::string friendlyName, unused;
		file >> unused >> friendlyName;
		if (friendlyName == "") break;

		if (meshObjects.find(friendlyName) == meshObjects.end()) continue;

		std::cout << "Loading models " << friendlyName << std::endl;
		cMeshObject *CurModel = meshObjects.at(friendlyName);

		file >> unused >> CurModel->meshName;
		file >> unused >> CurModel->position.x >> CurModel->position.y >> CurModel->position.z;
		file >> unused >> CurModel->postRotation.x >> CurModel->postRotation.y >> CurModel->postRotation.z;
		file >> unused >> CurModel->nonUniformScale.x >> CurModel->nonUniformScale.y >> CurModel->nonUniformScale.z;
		file >> unused >> CurModel->objColour.x >> CurModel->objColour.y >> CurModel->objColour.z;
	}
	file.close();
}




void loadLights(std::string filename, std::vector<sLight*> lights)
{
	std::ifstream file(("output/" + filename).c_str());

	if (!file.is_open()) { return; }

	std::map<std::string, sLight*> mapLights;
	for (unsigned int x = 0; x < lights.size(); x++)
	{
		std::string lightName = lights[x]->lightName;
		mapLights[lightName] = lights[x];
	}

	while (true)
	{
		std::string lightName, unused;
		file >> unused >> lightName;
		if (lightName == "") break;

		if (mapLights.find(lightName) == mapLights.end()) continue;

		std::cout << "Loading Lights " << lightName << std::endl;
		sLight *CurLight = mapLights.at(lightName);

		//file >> unused >> CurLight->lightName;
		file >> unused >> CurLight->position.x >> CurLight->position.y >> CurLight->position.z;
		file >> unused >> CurLight->atten.x >> CurLight->atten.y >> CurLight->atten.z;
		file >> unused >> CurLight->diffuse.x  >> CurLight->diffuse.y >> CurLight->diffuse.z >> CurLight->diffuse.w;
		file >> unused >> CurLight->param2.x;

	}
	file.close();
}


//void loadModels(std::string filename, std::vector<cMeshObject*> models) {
//	filename = "output/" + filename;
//	//cMeshObject* model1 = models.at(0);
//
//	std::ifstream f(filename.c_str());
//	if (!f.is_open()) {
//		//error
//	}
//	std::string nextData;
//
//
//	for (std::vector<cMeshObject*>::iterator it = models.begin(); it != models.end(); ++it)
//	{
//		cMeshObject* CurModel = *it;
//		while (f >> nextData) {
//			if (nextData == "Mesh_Name")
//			{
//				break;
//			};
//		}
//
//		if (f.eof()) {
//			std::cout << "error" << std::endl;//error
//		}
//		f >> nextData;
//															//f >> CurModel->meshName; // TODO verify that this string does not include '\n' character
//		if (nextData == CurModel->meshName) {
//			std::cout << CurModel->meshName << std::endl;
//
//			while (f >> nextData) {
//				if (nextData == "Position")
//				{
//					break;
//				};
//			}
//
//			if (f.eof()) {
//				//error
//			}
//
//			f >> CurModel->position.x;
//			f >> CurModel->position.y;
//			f >> CurModel->position.z;
//
//			std::cout << CurModel->position.x << std::endl;
//			std::cout << CurModel->position.y << std::endl;
//			std::cout << CurModel->position.z << std::endl;
//
//			while (f >> nextData) {
//				if (nextData == "Rotation")
//				{
//					break;
//				};
//			}
//			if (f.eof()) {
//				//error
//			}
//
//			f >> CurModel->postRotation.x;
//			f >> CurModel->postRotation.y;
//			f >> CurModel->postRotation.z;
//
//			std::cout << CurModel->postRotation.x << std::endl;
//			std::cout << CurModel->postRotation.y << std::endl;
//			std::cout << CurModel->postRotation.z << std::endl;
//
//
//			//Searching for Scale
//			while (f >> nextData) {
//				if (nextData == "Scale")
//				{
//					break;
//				};
//			}
//			if (f.eof()) {
//				//error
//			}
//
//			f >> CurModel->nonUniformScale.x;
//			f >> CurModel->nonUniformScale.y;
//			f >> CurModel->nonUniformScale.z;
//
//			std::cout << CurModel->nonUniformScale.x << std::endl;
//			std::cout << CurModel->nonUniformScale.y << std::endl;
//			std::cout << CurModel->nonUniformScale.z << std::endl;
//		}
//
//			while (f >> nextData) {
//				if (nextData == "Colour")
//				{
//					break;
//				};
//			}
//			if (f.eof()) {
//				//error
//			}
//
//			f >> CurModel->objColour.x;
//			f >> CurModel->objColour.y;
//			f >> CurModel->objColour.z;
//
//			std::cout << CurModel->objColour.x << std::endl;
//			std::cout << CurModel->objColour.y << std::endl;
//			std::cout << CurModel->objColour.z << std::endl;
//
//
//	}
//}













