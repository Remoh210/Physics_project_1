#include "globalOpenGLStuff.h"
#include "globalStuff.h"		// for g_pRogerRabbit

#include "cVAOMeshManager.h"
#include "cMeshObject.h"

#include "DebugRenderer/cDebugRenderer.h"

#include <iostream>

// Loading models was moved into this function
void LoadModelTypes( cVAOMeshManager* pTheVAOMeshManager, GLuint shaderProgramID )
{

	sModelDrawInfo tableInfo;
	tableInfo.meshFileName = "table.ply";					// "mig29_xyz.ply";
	pTheVAOMeshManager->LoadModelIntoVAO(tableInfo, shaderProgramID);

	sModelDrawInfo cubeInfo;
	cubeInfo.meshFileName = "cube.ply";					// "mig29_xyz.ply";
	pTheVAOMeshManager->LoadModelIntoVAO(cubeInfo, shaderProgramID);

	sModelDrawInfo torchInfo;
	torchInfo.meshFileName = "torch.ply";					// "mig29_xyz.ply";
	pTheVAOMeshManager->LoadModelIntoVAO(torchInfo, shaderProgramID);

	sModelDrawInfo teapotInfo;
	teapotInfo.meshFileName = "Utah_Teapot_xyz_n.ply";			// "Utah_Teapot_xyz.ply";
	pTheVAOMeshManager->LoadModelIntoVAO(teapotInfo, shaderProgramID);

	sModelDrawInfo terrainInfo;
	terrainInfo.meshFileName = "MeshLab_Fractal_Terrain_xyz_n.ply";	// "MeshLab_Fractal_Terrain_xyz.ply";
	// Will alow me to update the vertex data in the mesh
	terrainInfo.bVertexBufferIsDynamic = true;
	pTheVAOMeshManager->LoadModelIntoVAO(terrainInfo, shaderProgramID);
	
	sModelDrawInfo bluntInfo;
	bluntInfo.meshFileName = "blunt.ply";	// "MeshLab_Fractal_Terrain_xyz.ply";
	// Will alow me to update the vertex data in the mesh
	bluntInfo.bVertexBufferIsDynamic = true;
	pTheVAOMeshManager->LoadModelIntoVAO(bluntInfo, shaderProgramID);

	sModelDrawInfo sphereInfo;
	sphereInfo.meshFileName = "Sphere_320_faces_xyz_n.ply";			// "Sphere_320_faces_xyz.ply";
	pTheVAOMeshManager->LoadModelIntoVAO(sphereInfo, shaderProgramID);

	sModelDrawInfo roomInfo;
	roomInfo.meshFileName = "room.ply";			// "Sphere_320_faces_xyz.ply";
	pTheVAOMeshManager->LoadModelIntoVAO(roomInfo, shaderProgramID);

	sModelDrawInfo skullInfo;
	skullInfo.meshFileName = "skull.ply";	// "MeshLab_Fractal_Terrain_xyz.ply";
	// Will alow me to update the vertex data in the mesh
	skullInfo.bVertexBufferIsDynamic = true;
	pTheVAOMeshManager->LoadModelIntoVAO(skullInfo, shaderProgramID);

	sModelDrawInfo spiderInfo;
	spiderInfo.meshFileName = "spider.ply";	// "MeshLab_Fractal_Terrain_xyz.ply";
	// Will alow me to update the vertex data in the mesh
	spiderInfo.bVertexBufferIsDynamic = true;
	pTheVAOMeshManager->LoadModelIntoVAO(spiderInfo, shaderProgramID);

	// At this point, mesh in in GPU
	std::cout << "Mesh was loaded OK" << std::endl;

	return;
}

	
// Loads the models we are drawing into the vector
void LoadModelsIntoScene( std::vector<cMeshObject*> &vec_pObjectsToDraw )
{


	{
		sMesh* cubeTri = new sMesh();
		cMeshObject* pCube = new cMeshObject();
		pCube->position = glm::vec3(-170.0f, 0.0f, 0.0);
		pCube->pTheShape = cubeTri;
		//pSpider->postRotation = glm::vec3(0.0f, glm::radians(-20.0f), 0.0f);
		pCube->objColour = glm::vec3(0.5f, 0.5f, 1.0f);
		pCube->friendlyName = "CubeTriangles";
		pCube->bIsUpdatedByPhysics = true;
		pCube->bIsWireFrame = true;
		pCube->meshName = "cube.ply";
		pCube->bDontLight = true;
		pCube->bIsUpdatedByPhysics = true;
		pCube->shapeType = cMeshObject::MESH;
		//pCube->setUniformScale(50.0f);
		pCube->bIsVisible = true;
		vec_pObjectsToDraw.push_back(pCube);
	}


	{
		sMesh* pTerTri = new sMesh();
		cMeshObject* pTer = new cMeshObject();
		pTer->position = glm::vec3(20.0f, -100.0f, 250.0f);
		pTer->pTheShape = pTerTri;
		//pSpider->postRotation = glm::vec3(0.0f, glm::radians(-20.0f), 0.0f);
		pTer->objColour = glm::vec3(0.5f, 0.5f, 1.0f);
		pTer->friendlyName = "Terrain";
		pTer->bIsUpdatedByPhysics = true;
		pTer->bIsWireFrame = true;
		pTer->meshName = "MeshLab_Fractal_Terrain_xyz_n.ply";
		pTer->shapeType = cMeshObject::MESH;
		pTer->bIsVisible = true;
		pTer->bDontLight = true;
		vec_pObjectsToDraw.push_back(pTer);
	}





	{
		sMesh* RoomTri = new sMesh();
		cMeshObject* pRoom = new cMeshObject();
		pRoom->position = glm::vec3(0.0f, 0.0f, 300.0f);
		//pSpider->postRotation = glm::vec3(0.0f, glm::radians(-20.0f), 0.0f);
		pRoom->objColour = glm::vec3(0.74f, 0.86f, 1.0f);
		pRoom->friendlyName = "Room_Triange_collision";
		pRoom->meshName = "room.ply";
		pRoom->shapeType = cMeshObject::MESH;
		pRoom->pTheShape = RoomTri;
		pRoom->bIsUpdatedByPhysics = true;
		//spRoom->setUniformScale(50.0f);
		pRoom->bIsVisible = true;
		vec_pObjectsToDraw.push_back(pRoom);
	}


	{
		sAABB* RoomPhysicsBox = new sAABB();
		cMeshObject* pRoomBox = new cMeshObject();
		pRoomBox->position = glm::vec3(0.0f, 0.0f, -3500.0f);
		//pSpider->postRotation = glm::vec3(0.0f, glm::radians(-20.0f), 0.0f);
		pRoomBox->objColour = glm::vec3(0.85f, 0.86f, 1.0f);
		pRoomBox->friendlyName = "Room_AABB_Collision";
		pRoomBox->meshName = "room.ply";
		pRoomBox->shapeType = cMeshObject::AABB;
		RoomPhysicsBox->sizeXYZ = glm::vec3(780.0f, 332.0f, 780.0f);

		//RoomPhysicsBox->maxXYZ = glm::vec3(593.0f, 545.7f, 543.8f) + pRoomBox->position;
		//RoomPhysicsBox->minXYZ = glm::vec3(-9571.0f, -87.7f, -1000.8f) + pRoomBox->position;
		
		pRoomBox->pTheShape = RoomPhysicsBox;
		pRoomBox->bIsUpdatedByPhysics = true;
		//spRoom->setUniformScale(50.0f);
		pRoomBox->bIsVisible = true;
		vec_pObjectsToDraw.push_back(pRoomBox);
	}



	//cMeshObject* pRogerRabbit = NULL;

	const unsigned int NUMBER_OF_BALLS = 15;

	for (unsigned int count = 0; count != NUMBER_OF_BALLS; count++)
		// Updated physics object
	{	// This sphere is the tiny little debug sphere
		cMeshObject* pBouncyBall = new cMeshObject();
		pBouncyBall->objColour = glm::vec3(getRandBetween0and1<float>() * 1.0f - 0.0f,
			getRandBetween0and1<float>() * 1.0f - 0.0f,
			getRandBetween0and1<float>() * 1.0f - 0.0f);;
		float scale = 40.0f;
		pBouncyBall->nonUniformScale = glm::vec3(scale, scale, scale);
		pBouncyBall->friendlyName = "bouncyBall" + std::to_string(count);
		pBouncyBall->meshName = "Sphere_320_faces_xyz_n.ply";		// "Sphere_320_faces_xyz.ply";
		pBouncyBall->bIsWireFrame = false;

		pBouncyBall->position = glm::vec3(getRandBetween0and1<float>() * 1000.0f - 500.0f,
			getRandBetween0and1<float>() * 250.0f + 0.5f,
			getRandBetween0and1<float>() * 1500.0f - 600.0f);
		pBouncyBall->velocity = glm::vec3(getRandBetween0and1<float>() * 200.0f - 5.0f,
			getRandBetween0and1<float>() * 200.0f - 5.0f,
			getRandBetween0and1<float>() * 200.0f - 5.0f);
		pBouncyBall->accel = glm::vec3(0.0f, -5.0f, 0.0f);
		pBouncyBall->bIsUpdatedByPhysics = true;

		//		pBouncyBall->radius = 5.0f;	// Be careful

				// Set the type
		pBouncyBall->pTheShape = new sSphere(scale);
		pBouncyBall->shapeType = cMeshObject::SPHERE;

		//pBouncyBall->pDebugRenderer = ::g_pDebugRenderer;


		//pTerrain->nonUniformScale = glm::vec3(0.1f,0.1f,0.1f);
		vec_pObjectsToDraw.push_back(pBouncyBall);
	}




	{	// This sphere is the tiny little debug sphere
		cMeshObject* pDebugSphere = new cMeshObject();
		pDebugSphere->position = glm::vec3(+150.0f, 0.0f, 0.0f);
		pDebugSphere->objColour = glm::vec3(0.0f, 1.0f, 0.0f);
		float scale = 30.0f;
		pDebugSphere->friendlyName = "AttenSphere";
		pDebugSphere->nonUniformScale = glm::vec3(scale, scale, scale);
		pDebugSphere->meshName = "Sphere_320_faces_xyz_n.ply";		
		pDebugSphere->bIsWireFrame = true;
		pDebugSphere->bIsVisible = false;
		pDebugSphere->pDebugRenderer = ::g_pDebugRenderer;

		vec_pObjectsToDraw.push_back(pDebugSphere);
	}



	{	// This sphere is the tiny little debug sphere
		
		cMeshObject* PhysicsSphere = new cMeshObject();
		PhysicsSphere->position = glm::vec3(200.0f, 0.0f, 0.0f);
		PhysicsSphere->objColour = glm::vec3(0.0f, 1.0f, 0.0f);
		float scale = 30.0f;
		sSphere* pSp = new sSphere(scale);
		PhysicsSphere->pTheShape = pSp;
		PhysicsSphere->friendlyName = "Debug";
		PhysicsSphere->nonUniformScale = glm::vec3(scale, scale, scale);
		PhysicsSphere->meshName = "Sphere_320_faces_xyz_n.ply";
		PhysicsSphere->shapeType = cMeshObject::SPHERE;
		PhysicsSphere->bIsWireFrame = true;
		PhysicsSphere->bIsVisible = true;
		PhysicsSphere->bIsUpdatedByPhysics = true;
		PhysicsSphere->pDebugRenderer = ::g_pDebugRenderer;

		vec_pObjectsToDraw.push_back(PhysicsSphere);
	}
	// ENDOF: Updated physics object


	{	// This sphere is the tiny little debug sphere
		cMeshObject* pShootBall = new cMeshObject();
		pShootBall->objColour = glm::vec3(1.0f, 105.0f / 255.0f, 180.0f / 255.0f);
		float scale = 60.0f;
		pShootBall->friendlyName = "shootBall";
		pShootBall->nonUniformScale = glm::vec3(scale, scale, scale);
		pShootBall->meshName = "Sphere_320_faces_xyz_n.ply";
		pShootBall->bIsWireFrame = false;

		//pShootBall->position = glm::vec3(getRandBetween0and1<float>() * 299.0f - 99.0f,
		//	getRandBetween0and1<float>() * 199.0f + 0.5f,
		//	getRandBetween0and1<float>() * 299.0f - 99.0f);
		//pShootBall->velocity = 
		pShootBall->accel = glm::vec3(0.0f, -5.0f, 0.0f);
		pShootBall->bIsUpdatedByPhysics = true;

		pShootBall->pTheShape = new sSphere(scale);
		pShootBall->shapeType = cMeshObject::SPHERE;

		//pShootBall->pDebugRenderer = ::g_pDebugRenderer;


		//pTerrain->nonUniformScale = glm::vec3(0.1f,0.1f,0.1f);
		vec_pObjectsToDraw.push_back(pShootBall);
	}

	cLightManager* lightmanager;
	saveLightInfo("ligths_default.txt", lightmanager->vecLights);
	saveModelInfo("models_default.txt", vec_pObjectsToDraw);

	return;
}