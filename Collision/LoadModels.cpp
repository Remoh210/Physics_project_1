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

	sModelDrawInfo roofInfo;
	roofInfo.meshFileName = "roof.ply";			// "Utah_Teapot_xyz.ply";
	pTheVAOMeshManager->LoadModelIntoVAO(roofInfo, shaderProgramID);

	sModelDrawInfo cube_flat_verticalInfo;
	cube_flat_verticalInfo.meshFileName = "cube_flat_vertical.ply";			// "Utah_Teapot_xyz.ply";
	pTheVAOMeshManager->LoadModelIntoVAO(cube_flat_verticalInfo, shaderProgramID);

	sModelDrawInfo cube_flat_vertical_vInfo;
	cube_flat_vertical_vInfo.meshFileName = "cube_flat_vertical_v.ply";			// "Utah_Teapot_xyz.ply";
	pTheVAOMeshManager->LoadModelIntoVAO(cube_flat_vertical_vInfo, shaderProgramID);
	
	sModelDrawInfo cube_flat_horizontalInfo;
	cube_flat_horizontalInfo.meshFileName = "cube_flat_horizontal.ply";			// "Utah_Teapot_xyz.ply";
	pTheVAOMeshManager->LoadModelIntoVAO(cube_flat_horizontalInfo, shaderProgramID);

	sModelDrawInfo cube_trig1;
	cube_trig1.meshFileName = "cube_trig_1.ply";			// "Utah_Teapot_xyz.ply";
	pTheVAOMeshManager->LoadModelIntoVAO(cube_trig1, shaderProgramID);

	sModelDrawInfo cube_trig2;
	cube_trig2.meshFileName = "cube_trig_2.ply";			// "Utah_Teapot_xyz.ply";
	pTheVAOMeshManager->LoadModelIntoVAO(cube_trig2, shaderProgramID);

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
		pTer->position = glm::vec3(-200.0f, -230.0f, 190.0f);
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
		sMesh* pRoofTri = new sMesh();
		//sAABB* RoofAABB = new sAABB();
		cMeshObject* pRoof = new cMeshObject(); //-175 510 35
		pRoof->position = glm::vec3(-175.0f, 510.0f, 35.0f);
		pRoof->pTheShape = pRoofTri;
		//pSpider->postRotation = glm::vec3(0.0f, glm::radians(-20.0f), 0.0f);
		pRoof->objColour = glm::vec3(0.5f, 0.5f, 1.0f);
		pRoof->friendlyName = "roof";
		pRoof->bIsUpdatedByPhysics = true;
		pRoof->bIsWireFrame = true;
		pRoof->meshName = "roof.ply";
		pRoof->bDontLight = true;
		pRoof->bIsUpdatedByPhysics = true;
		//RoofAABB->sizeXYZ = glm::vec3(800.0f, 100.0f, 800.0f);
		pRoof->shapeType = cMeshObject::MESH;
		//pCubeFlat3->shapeType = cMeshObject::AABB;
		//pCube->setUniformScale(50.0f);
		pRoof->bIsVisible = true;
		vec_pObjectsToDraw.push_back(pRoof);
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
		//sAABB* RoomPhysicsBox = new sAABB();
		cMeshObject* pRoomBox = new cMeshObject();
		pRoomBox->position = glm::vec3(0.0f, 0.0f, -3500.0f);
		//pSpider->postRotation = glm::vec3(0.0f, glm::radians(-20.0f), 0.0f);
		pRoomBox->objColour = glm::vec3(0.85f, 0.86f, 1.0f);
		pRoomBox->friendlyName = "Room_AABB_Collision";
		pRoomBox->meshName = "room.ply";
		//pRoomBox->shapeType = cMeshObject::AABB;
		//RoomPhysicsBox->sizeXYZ = glm::vec3(780.0f, 332.0f, 780.0f);

		//RoomPhysicsBox->maxXYZ = glm::vec3(593.0f, 545.7f, 543.8f) + pRoomBox->position;
		//RoomPhysicsBox->minXYZ = glm::vec3(-9571.0f, -87.7f, -1000.8f) + pRoomBox->position;
		
		//pRoomBox->pTheShape = RoomPhysicsBox;
		pRoomBox->bIsUpdatedByPhysics = false;
		//spRoom->setUniformScale(50.0f);
		pRoomBox->bIsVisible = false;
		//vec_pObjectsToDraw.push_back(pRoomBox);
	}


	{
		sAABB* cubeFlatPh1 = new sAABB();
		cMeshObject* pCubeFlat1 = new cMeshObject();//-945 160 -3770
		pCubeFlat1->position = glm::vec3(-945.0f, 160.0f, -3770.0);
		pCubeFlat1->pTheShape = cubeFlatPh1;
		//pSpider->postRotation = glm::vec3(0.0f, glm::radians(-20.0f), 0.0f);
		pCubeFlat1->objColour = glm::vec3(0.5f, 0.5f, 1.0f);
		pCubeFlat1->friendlyName = "flatCube1";
		pCubeFlat1->bIsUpdatedByPhysics = true;
		pCubeFlat1->bIsWireFrame = false;
		pCubeFlat1->meshName = "cube_flat_vertical.ply";
		pCubeFlat1->bDontLight = false;
		pCubeFlat1->bIsUpdatedByPhysics = true;
		cubeFlatPh1->sizeXYZ = glm::vec3(100.0f, 800.0f, 800.0f);
		pCubeFlat1->shapeType = cMeshObject::AABB;
		//pCube->setUniformScale(50.0f);
		pCubeFlat1->bIsVisible = true;
		vec_pObjectsToDraw.push_back(pCubeFlat1);
	}



	{
		sAABB* cubeFlatPh2 = new sAABB();
		cMeshObject* pCubeFlat2 = new cMeshObject();//-945 160 -3770
		pCubeFlat2->position = glm::vec3(565.0f, 160.0f, -3770.0f);
		pCubeFlat2->pTheShape = cubeFlatPh2;
		//pSpider->postRotation = glm::vec3(0.0f, glm::radians(-20.0f), 0.0f);
		pCubeFlat2->objColour = glm::vec3(0.5f, 0.5f, 1.0f);
		pCubeFlat2->friendlyName = "flatCube2";
		pCubeFlat2->bIsUpdatedByPhysics = true;
		pCubeFlat2->bIsWireFrame = false;
		pCubeFlat2->meshName = "cube_flat_vertical.ply";
		pCubeFlat2->bDontLight = false;
		pCubeFlat2->bIsUpdatedByPhysics = true;
		cubeFlatPh2->sizeXYZ = glm::vec3(100.0f, 800.0f, 800.0f);
		pCubeFlat2->shapeType = cMeshObject::AABB;
		//pCube->setUniformScale(50.0f);
		pCubeFlat2->bIsVisible = true;
		vec_pObjectsToDraw.push_back(pCubeFlat2);
	}

	{
		sAABB* cubeFlatV_ph = new sAABB();
		cMeshObject* cubeFlatV = new cMeshObject();//-945 160 -3770
		cubeFlatV->position = glm::vec3(-225.0f, 100.0f, -3000.0f);
		cubeFlatV->pTheShape = cubeFlatV_ph;
		//pSpider->postRotation = glm::vec3(0.0f, glm::radians(-20.0f), 0.0f);
		cubeFlatV->objColour = glm::vec3(0.5f, 0.5f, 1.0f);
		cubeFlatV->friendlyName = "flatCube_v";
		cubeFlatV->bIsUpdatedByPhysics = true;
		cubeFlatV->bIsWireFrame = false;
		cubeFlatV->meshName = "cube_flat_vertical_v.ply";
		cubeFlatV->bDontLight = false;
		cubeFlatV->bIsUpdatedByPhysics = true;
		cubeFlatV_ph->sizeXYZ = glm::vec3(800.0f, 800.0f, 100.0f);
		cubeFlatV->shapeType = cMeshObject::AABB;
		//pCube->setUniformScale(50.0f);
		cubeFlatV->bIsVisible = true;
		vec_pObjectsToDraw.push_back(cubeFlatV);
	}


	{
		sAABB* cubeFlatV_ph2 = new sAABB();
		cMeshObject* cubeFlatV2 = new cMeshObject();//-165 180 -4470
		cubeFlatV2->position = glm::vec3(-165.0f, 180.0f, -4470.0f);
		cubeFlatV2->pTheShape = cubeFlatV_ph2;
		//pSpider->postRotation = glm::vec3(0.0f, glm::radians(-20.0f), 0.0f);
		cubeFlatV2->objColour = glm::vec3(0.5f, 0.5f, 1.0f);
		cubeFlatV2->friendlyName = "flatCube_v";
		cubeFlatV2->bIsUpdatedByPhysics = true;
		cubeFlatV2->bIsWireFrame = false;
		cubeFlatV2->meshName = "cube_flat_vertical_v.ply";
		cubeFlatV2->bDontLight = false;
		cubeFlatV2->bIsUpdatedByPhysics = true;
		cubeFlatV_ph2->sizeXYZ = glm::vec3(800.0f, 800.0f, 100.0f);
		cubeFlatV2->shapeType = cMeshObject::AABB;
		//pCube->setUniformScale(50.0f);
		cubeFlatV2->bIsVisible = true;
		vec_pObjectsToDraw.push_back(cubeFlatV2);
	}


	{
		sAABB* cubeFlatPh3 = new sAABB();
		cMeshObject* pCubeFlat3 = new cMeshObject();//-945 160 -3770
		pCubeFlat3->position = glm::vec3(-150.0f, 900.0f, -3770.0);
		pCubeFlat3->pTheShape = cubeFlatPh3;
		//pSpider->postRotation = glm::vec3(0.0f, glm::radians(-20.0f), 0.0f);
		pCubeFlat3->objColour = glm::vec3(0.5f, 0.5f, 1.0f);
		pCubeFlat3->friendlyName = "flatCube3_horizontal";
		pCubeFlat3->bIsUpdatedByPhysics = true;
		pCubeFlat3->bIsWireFrame = false;
		pCubeFlat3->meshName = "cube_flat_horizontal.ply";
		pCubeFlat3->bDontLight = false;
		pCubeFlat3->bIsUpdatedByPhysics = true;
		cubeFlatPh3->sizeXYZ = glm::vec3(800.0f, 100.0f, 800.0f);
		pCubeFlat3->shapeType = cMeshObject::AABB;
		//pCube->setUniformScale(50.0f);
		pCubeFlat3->bIsVisible = true;
		vec_pObjectsToDraw.push_back(pCubeFlat3);
	}


	{
		sAABB* cubeFlatPh4 = new sAABB();
		cMeshObject* pCubeFlat4 = new cMeshObject();//-945 160 -3770
		pCubeFlat4->position = glm::vec3(-150.0f, -600.0f, -3770.0);
		pCubeFlat4->pTheShape = cubeFlatPh4;
		//pSpider->postRotation = glm::vec3(0.0f, glm::radians(-20.0f), 0.0f);
		pCubeFlat4->objColour = glm::vec3(0.5f, 0.5f, 1.0f);
		pCubeFlat4->friendlyName = "flatCube3_horizontal2";
		pCubeFlat4->bIsUpdatedByPhysics = true;
		pCubeFlat4->bIsWireFrame = false;
		pCubeFlat4->meshName = "cube_flat_horizontal.ply";
		pCubeFlat4->bDontLight = false;
		pCubeFlat4->bIsUpdatedByPhysics = true;
		cubeFlatPh4->sizeXYZ = glm::vec3(800.0f, 100.0f, 800.0f);
		pCubeFlat4->shapeType = cMeshObject::AABB;
		//pCube->setUniformScale(50.0f);
		pCubeFlat4->bIsVisible = true;
		vec_pObjectsToDraw.push_back(pCubeFlat4);
	}

	//Trigger Cubes


	{
		sAABB* trigcube1 = new sAABB();
		cMeshObject* pTrigCube = new cMeshObject();//-945 160 -3770
		 pTrigCube->position = glm::vec3(-200.0f, -100.0f, -3400.0f);
		 pTrigCube->pTheShape = trigcube1;
		//pSpider->postRotation = glm::vec3(0.0f, glm::radians(-20.0f), 0.0f);
		 pTrigCube->objColour = glm::vec3(0.3f, 0.7f, 0.6f);
		 pTrigCube->friendlyName = "trigcube";
		 pTrigCube->bIsUpdatedByPhysics = true;
		 pTrigCube->bIsWireFrame = false;
		 pTrigCube->meshName = "cube_trig_1.ply";
		 pTrigCube->bDontLight = false;
		 pTrigCube->bIsUpdatedByPhysics = true;
		 trigcube1->sizeXYZ = glm::vec3(315.0f, 52.0f, 123.0f);
		 pTrigCube->shapeType = cMeshObject::AABB;
		//pCube->setUniformScale(50.0f);
		 pTrigCube->bIsVisible = true;
		vec_pObjectsToDraw.push_back(pTrigCube);
	}


	{
		sAABB* trigcube2 = new sAABB();
		cMeshObject* pTrigCube2 = new cMeshObject();//-945 160 -3770
		pTrigCube2->position = glm::vec3(-100.0f, -200.0f, -4100.0f);
		pTrigCube2->pTheShape = trigcube2;
		//pSpider->postRotation = glm::vec3(0.0f, glm::radians(-20.0f), 0.0f);
		pTrigCube2->objColour = glm::vec3(0.0f, 0.3f, 0.9f);
		pTrigCube2->friendlyName = "trigcube";
		pTrigCube2->bIsUpdatedByPhysics = true;
		pTrigCube2->bIsWireFrame = false;
		pTrigCube2->meshName = "cube_trig_2.ply";
		pTrigCube2->bDontLight = false;
		pTrigCube2->bIsUpdatedByPhysics = true;
		trigcube2->sizeXYZ = glm::vec3(92.0f, 280.0f, 122.0f);
		pTrigCube2->shapeType = cMeshObject::AABB;
		//pCube->setUniformScale(50.0f);
		pTrigCube2->bIsVisible = true;
		vec_pObjectsToDraw.push_back(pTrigCube2);
	}



	//cMeshObject* pRogerRabbit = NULL;

	const unsigned int NUMBER_OF_BALLS = 15;

	for (unsigned int count = 0; count != NUMBER_OF_BALLS; count++)
		// Updated physics object
	{	// This sphere is the tiny little debug sphere
		cMeshObject* pBouncyBall = new cMeshObject();
		pBouncyBall->objColour = glm::vec3(getRandBetween0and1<float>() * 1.0f - 0.0f,
			getRandBetween0and1<float>() * 1.0f - 0.0f,
			getRandBetween0and1<float>() * 1.0f - 0.0f);
		float scale = 40.0f;
		pBouncyBall->nonUniformScale = glm::vec3(scale, scale, scale);
		pBouncyBall->friendlyName = "bouncyBall" + std::to_string(count);
		pBouncyBall->meshName = "Sphere_320_faces_xyz_n.ply";		// "Sphere_320_faces_xyz.ply";
		pBouncyBall->bIsWireFrame = false;
		pBouncyBall->bRandomGenObj = true;
	

		pBouncyBall->position = glm::vec3(getRandBetween0and1<float>() * 1000.0f - 500.0f,
			getRandBetween0and1<float>() * 250.0f + 0.5f,
			getRandBetween0and1<float>() * 1500.0f - 600.0f);
		pBouncyBall->initial_position = pBouncyBall->position;
		pBouncyBall->velocity = glm::vec3(getRandBetween0and1<float>() * 200.0f - 5.0f,
			getRandBetween0and1<float>() * 200.0f - 5.0f,
			getRandBetween0and1<float>() * 200.0f - 5.0f);
		pBouncyBall->initia_vel = pBouncyBall->velocity;
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




	int NUMBER_OF_BALL_AABB = 20;
	for (unsigned int count = 0; count != NUMBER_OF_BALL_AABB; count++)
		// Updated physics object
	{	// This sphere is the tiny little debug sphere
		cMeshObject* pBouncyBall = new cMeshObject();
		pBouncyBall->objColour = glm::vec3(getRandBetween0and1<float>() * 1.0f - 0.0f,
			getRandBetween0and1<float>() * 1.0f - 0.0f,
			getRandBetween0and1<float>() * 1.0f - 0.0f);
		float scale = 40.0f;
		pBouncyBall->nonUniformScale = glm::vec3(scale, scale, scale);
		pBouncyBall->friendlyName = "bouncyBall_AABB" + std::to_string(count);
		pBouncyBall->meshName = "Sphere_320_faces_xyz_n.ply";		// "Sphere_320_faces_xyz.ply";
		pBouncyBall->bIsWireFrame = false;
		pBouncyBall->bRandomGenObj = true;

		if (count < 10) {
			pBouncyBall->position = glm::vec3((count * 100.0f) - 600.0f, -100.0f, -3600.0f);
		}
		else if (count >= 10) {
			pBouncyBall->position = glm::vec3((count * 100.0f) - 1600.0f, -100.0f, -3800.0f);
		}
		//pBouncyBall->position = glm::vec3(getRandBetween0and1<float>() * 1000.0f - 500.0f,
			//getRandBetween0and1<float>() * 250.0f + 0.5f,
			//getRandBetween0and1<float>() * -3000.0f - 3100.0f);
		pBouncyBall->initial_position = pBouncyBall->position;
		//pBouncyBall->velocity = glm::vec3(getRandBetween0and1<float>() * 200.0f - 5.0f,
		//	getRandBetween0and1<float>() * 200.0f - 5.0f,
		//	getRandBetween0and1<float>() * 200.0f - 5.0f);
		//pBouncyBall->accel = glm::vec3(0.0f, -5.0f, 0.0f);
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




	// ENDOF: Updated physics object


	{	// This sphere is the tiny little debug sphere
		cMeshObject* pShootBall = new cMeshObject();
		pShootBall->objColour = glm::vec3(1.0f, 95.0f / 255.0f, 130.0f / 255.0f);
		float scale = 60.0f;
		pShootBall->friendlyName = "shootBall";
		pShootBall->nonUniformScale = glm::vec3(scale, scale, scale);
		pShootBall->meshName = "Sphere_320_faces_xyz_n.ply";
		pShootBall->bIsWireFrame = false;
		pShootBall->bIsUpdatedByPhysics = false;

		//pShootBall->position = glm::vec3(getRandBetween0and1<float>() * 299.0f - 99.0f,
		//	getRandBetween0and1<float>() * 199.0f + 0.5f,
		//	getRandBetween0and1<float>() * 299.0f - 99.0f);
		//pShootBall->velocity = 
		pShootBall->accel = glm::vec3(0.0f, -5.0f, 0.0f);
		pShootBall->bIsUpdatedByPhysics = true;

		pShootBall->pTheShape = new sSphere(scale);
		pShootBall->shapeType = cMeshObject::SPHERE;
		pShootBall->bIsVisible = false;


		//pShootBall->pDebugRenderer = ::g_pDebugRenderer;


		//pTerrain->nonUniformScale = glm::vec3(0.1f,0.1f,0.1f);
		vec_pObjectsToDraw.push_back(pShootBall);
	}

	cLightManager* lightmanager;
	saveLightInfo("ligths_default.txt", lightmanager->vecLights);
	saveModelInfo("models_default.txt", vec_pObjectsToDraw);

	return;
}