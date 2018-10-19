//     ___                 ___ _     
//    / _ \ _ __  ___ _ _ / __| |    
//   | (_) | '_ \/ -_) ' \ (_ | |__  
//    \___/| .__/\___|_||_\___|____| 
//         |_|                       
//
#include "globalOpenGLStuff.h"
#include "globalStuff.h"

#include <glm/glm.hpp>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

#include <stdlib.h>
#include <stdio.h>		// printf();
#include <iostream>		// cout (console out)

#include <vector>		// "smart array" dynamic array

#include "cShaderManager.h"
#include "cMeshObject.h"
#include "cVAOMeshManager.h"

#include "DebugRenderer/cDebugRenderer.h"
#include "cLightHelper.h"

cDebugRenderer* g_pDebugRendererACTUAL = NULL;
iDebugRenderer* g_pDebugRenderer = NULL;


void UpdateWindowTitle(void);


void DoPhysicsUpdate( double deltaTime, 
					  std::vector< cMeshObject* > &vec_pObjectsToDraw );

std::vector< cMeshObject* > vec_pObjectsToDraw;

// To the right, up 4.0 units, along the x axis
glm::vec3 g_lightPos = glm::vec3( 4.0f, 4.0f, 0.0f );
float g_lightBrightness = 400000.0f;

unsigned int numberOfObjectsToDraw = 0;

const unsigned int SCR_WIDTH = 1024;
const unsigned int SCR_HEIGHT = 800;


glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 g_CameraEye = glm::vec3( 0.0, 0.0, 250.0f );

glm::vec3 Front;
glm::vec3 Horizontal;

//glm::vec3 g_CameraAt = glm::vec3(g_CameraEye, g_CameraEye.z + cameraFront.z, cameraUp.y);
//glm::vec3 g_CameraAt = glm::vec3( 0.0, 0.0, 0.0f );


cShaderManager* pTheShaderManager = NULL;		// "Heap" variable
cVAOMeshManager* g_pTheVAOMeshManager = NULL;

cLightManager* LightManager = NULL;


static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}


int main(void)
{
	GLFWwindow* window;

	glfwSetErrorCallback(error_callback);

	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Light", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}





	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);

	//glfwSetKeyCallback()
	

	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glfwSwapInterval(1);


	// Create the shader manager...
	//cShaderManager TheShaderManager;		// 
	//cShaderManager* pTheShaderManager;		// 
	pTheShaderManager = new cShaderManager();
	pTheShaderManager->setBasePath("assets/shaders/");

	cShaderManager::cShader vertexShader;
	cShaderManager::cShader fragmentShader;

	vertexShader.fileName = "vertex01.glsl";
	vertexShader.shaderType = cShaderManager::cShader::VERTEX_SHADER;

	fragmentShader.fileName = "fragment01.glsl";
	fragmentShader.shaderType = cShaderManager::cShader::FRAGMENT_SHADER;

	if (pTheShaderManager->createProgramFromFile("BasicUberShader",
		vertexShader,
		fragmentShader))
	{		// Shaders are OK
		std::cout << "Compiled shaders OK." << std::endl;
	}
	else
	{
		std::cout << "OH NO! Compile error" << std::endl;
		std::cout << pTheShaderManager->getLastError() << std::endl;
	}



	GLuint program = pTheShaderManager->getIDFromFriendlyName("BasicUberShader");


	::g_pTheVAOMeshManager = new cVAOMeshManager();


	// Loading the uniform variables here (rather than the inner draw loop)
	GLint objectColour_UniLoc = glGetUniformLocation(program, "objectColour");
	//uniform vec3 lightPos;
	//uniform float lightAtten;
	GLint lightPos_UniLoc = glGetUniformLocation(program, "lightPos");
	GLint lightBrightness_UniLoc = glGetUniformLocation(program, "lightBrightness");

	//	// uniform mat4 MVP;	THIS ONE IS NO LONGER USED	
	//uniform mat4 matModel;	// M
	//uniform mat4 matView;		// V
	//uniform mat4 matProj;		// P
	//GLint mvp_location = glGetUniformLocation(program, "MVP");
	GLint matModel_location = glGetUniformLocation(program, "matModel");
	GLint matView_location = glGetUniformLocation(program, "matView");
	GLint matProj_location = glGetUniformLocation(program, "matProj");


	// Note that this point is to the +interface+ but we're creating the actual object
	::g_pDebugRendererACTUAL = new cDebugRenderer();
	::g_pDebugRenderer = (iDebugRenderer*)::g_pDebugRendererACTUAL;

	if (!::g_pDebugRendererACTUAL->initialize())
	{
		std::cout << "Warning: couldn't init the debug renderer." << std::endl;
		std::cout << "\t" << ::g_pDebugRendererACTUAL->getLastError() << std::endl;
	}
	else
	{
		std::cout << "Debug renderer is OK" << std::endl;
	}

	// Loading models was moved into this function
	LoadModelTypes(::g_pTheVAOMeshManager, program);
	LoadModelsIntoScene(::vec_pObjectsToDraw);

	// Get the current time to start with
	double lastTime = glfwGetTime();


	//***************************************************************

	LightManager = new cLightManager();
	sLight* pTheOneLight = NULL;
	sLight* pTheSecondLight = NULL;
	sLight* pTheThirdLight = NULL;
	sLight* pTheForthLight = NULL;
	sLight* pTheFifthLight = NULL;
	sLight* pTheSixthLight = NULL;


	{
		pTheForthLight = new sLight();
		pTheForthLight->position = glm::vec4(1.0f, 400.0f, 0.0f, 1.0f);
		pTheForthLight->atten.x = 0.0f;	// 			float constAtten = 0.0f;
		pTheForthLight->atten.y = 0.0001f;	//			float linearAtten = 0.01f;
		pTheForthLight->atten.z = 0.00001f;	//			float quadAtten = 0.001f;
		pTheForthLight->diffuse = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);// White light
		pTheForthLight->param2.x = 1.0f;
		pTheForthLight->lightName = "MainLight";
		LightManager->vecLights.push_back(pTheForthLight);
		LightManager->LoadUniformLocations(program);
	}



	{
		pTheFifthLight = new sLight();//-29 450 -3660
		pTheFifthLight->position = glm::vec4(-204.0f, 165.0f, -3750.0f, 1.0f);
		pTheFifthLight->atten.x = 0.0f;	// 			float constAtten = 0.0f;
		pTheFifthLight->atten.y = 0.000004f;	//			float linearAtten = 0.01f;
		pTheFifthLight->atten.z = 0.000002f;	//			float quadAtten = 0.001f;
		pTheFifthLight->diffuse = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);// White light
		pTheFifthLight->param2.x = 1.0f;
		pTheFifthLight->lightName = "MainLight2";
		LightManager->vecLights.push_back(pTheFifthLight);
		LightManager->LoadUniformLocations(program);
	}



	{
		pTheSixthLight = new sLight();//-29 450 -3660
		pTheSixthLight->position = glm::vec4(-124.0f, 2870.0f, -1465.0f, 1.0f);
		pTheSixthLight->atten.x = 0.0f;	// 			float constAtten = 0.0f;
		pTheSixthLight->atten.y = 0.0004934f;	//			float linearAtten = 0.01f;
		pTheSixthLight->atten.z = 0.00000077f;	//			float quadAtten = 0.001f;
		pTheSixthLight->diffuse = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);// White light
		pTheSixthLight->param2.x = 1.0f;
		pTheSixthLight->lightName = "MainLight3";
		LightManager->vecLights.push_back(pTheSixthLight);
		LightManager->LoadUniformLocations(program);
	}

	{

		pTheOneLight = new sLight();
		pTheOneLight->position = glm::vec4(-60.0f, 70.0f, 0.0f, 1.0f);
		pTheOneLight->atten.x = 0.0f;	// 			float constAtten = 0.0f;
		pTheOneLight->atten.y = 0.001f;	//			float linearAtten = 0.01f;
		pTheOneLight->atten.z = 0.0001f;	//			float quadAtten = 0.001f;
		pTheOneLight->diffuse = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);// White light
		pTheOneLight->param2.x = 1.0f;
		pTheOneLight->lightName = "pTheRedLight";
		//pTheOneLight->AtenSphere = false;
		LightManager->vecLights.push_back(pTheOneLight);
		LightManager->LoadUniformLocations(program);
	}

	{
		pTheSecondLight = new sLight();
		pTheSecondLight->position = glm::vec4(0.0f, 70.0f, 0.0f, 1.0f);
		pTheSecondLight->atten.x = 0.0f;	// 			float constAtten = 0.0f;
		pTheSecondLight->atten.y = 0.01f;	//			float linearAtten = 0.01f;
		pTheSecondLight->atten.z = 0.0001f;	//			float quadAtten = 0.001f;
		pTheSecondLight->diffuse = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);// White light
		pTheSecondLight->param2.x = 1.0f;
		pTheSecondLight->lightName = "pTheSecondLight";
		//pTheSecondLight->AtenSphere = false;
		LightManager->vecLights.push_back(pTheSecondLight);
		LightManager->LoadUniformLocations(program);
	}

	{
		pTheThirdLight = new sLight();
		pTheThirdLight->position = glm::vec4(60.0f, 70.0f, 0.0f, 1.0f);
		pTheThirdLight->atten.x = 0.0f;	// 			float constAtten = 0.0f;
		pTheThirdLight->atten.y = 0.01f;	//			float linearAtten = 0.01f;
		pTheThirdLight->atten.z = 0.0001f;	//			float quadAtten = 0.001f;
		pTheThirdLight->diffuse = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);// White light
		pTheThirdLight->lightName = "pTheThirdLight";
		pTheThirdLight->param2.x = 1.0f;
		//pTheThirdLight->AtenSphere = false;
		LightManager->vecLights.push_back(pTheThirdLight);
		LightManager->LoadUniformLocations(program);
	}



	cLightHelper* pLightHelper = new cLightHelper();

	
	//Reload from the file
	//loadModels("Models.txt", vec_pObjectsToDraw);
	//*****************************************************************
	
	// Draw the "scene" (run the program)
	while (!glfwWindowShouldClose(window))
    {

		// Switch to the shader we want
		::pTheShaderManager->useShaderProgram( "BasicUberShader" );

        float ratio;
        int width, height;

		//Front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
		//Front.y = sin(glm::radians(pitch));
		//Front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
		//cameraFront = glm::normalize(Front);
		//Horizontal = glm::normalize(glm::cross(Front, cameraUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
		//Up = glm::normalize(glm::cross(Right, Front));


		glm::mat4x4 matProjection = glm::mat4(1.0f);
		glm::mat4x4	matView = glm::mat4(1.0f);
 

        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float) height;
        glViewport(0, 0, width, height);


		glEnable( GL_DEPTH );		// Enables the KEEPING of the depth information
		glEnable( GL_DEPTH_TEST );	// When drawing, checked the existing depth
		glEnable( GL_CULL_FACE );	// Discared "back facing" triangles

		// Colour and depth buffers are TWO DIFF THINGS.
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		//mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
		matProjection = glm::perspective( 1.0f,			// FOV
			                                ratio,		// Aspect ratio
			                                0.1f,			// Near clipping plane
			                                5000.0f );	// Far clipping plane

		matView = glm::lookAt(g_CameraEye, g_CameraEye + cameraFront, cameraUp);

		//matView = glm::lookAt( g_CameraEye,	// Eye
		//	                    g_CameraAt,		// At
		//	                    glm::vec3( 0.0f, 1.0f, 0.0f ) );// Up

		glUniformMatrix4fv( matView_location, 1, GL_FALSE, glm::value_ptr(matView));
		glUniformMatrix4fv( matProj_location, 1, GL_FALSE, glm::value_ptr(matProjection));
		// Do all this ONCE per frame
		LightManager->CopyLightValuesToShader();
			




		// Draw all the objects in the "scene"
		for ( unsigned int objIndex = 0; 
			  objIndex != (unsigned int)vec_pObjectsToDraw.size(); 
			  objIndex++ )
		{	
			cMeshObject* pCurrentMesh = vec_pObjectsToDraw[objIndex];
			
			glm::mat4x4 matModel = glm::mat4(1.0f);			// mat4x4 m, p, mvp;

			DrawObject(pCurrentMesh, matModel, program);

		}//for ( unsigned int objIndex = 0; 


		// High res timer (likely in ms or ns)
		double currentTime = glfwGetTime();		
		double deltaTime = currentTime - lastTime; 

		for ( unsigned int objIndex = 0; 
			  objIndex != (unsigned int)vec_pObjectsToDraw.size(); 
			  objIndex++ )
		{	
			cMeshObject* pCurrentMesh = vec_pObjectsToDraw[objIndex];
			
			pCurrentMesh->Update( deltaTime );

		}//for ( unsigned int objIndex = 0; 


		// Call the debug renderer call
//#ifdef _DEBUG
		::g_pDebugRendererACTUAL->RenderDebugObjects( matView, matProjection, deltaTime );
//#endif 


		// update the "last time"
		lastTime = currentTime;

		// The physics update loop
		DoPhysicsUpdate( deltaTime, vec_pObjectsToDraw );




		//*****************************************************************************************
	for (std::vector<sLight*>::iterator it = LightManager->vecLights.begin(); it != LightManager->vecLights.end(); ++it)
	{

		sLight* CurLight = *it;
		if (CurLight->AtenSphere == true) {

			cMeshObject* pDebugSphere = findObjectByFriendlyName("AttenSphere");
			pDebugSphere->bIsVisible = true;
			pDebugSphere->bDontLight = true;
			glm::vec3 oldColour = pDebugSphere->objColour;
			glm::vec3 oldScale = pDebugSphere->nonUniformScale;
			pDebugSphere->objColour = glm::vec3(255.0f / 255.0f, 105.0f / 255.0f, 180.0f / 255.0f);
			pDebugSphere->bUseVertexColour = false;
			pDebugSphere->position = glm::vec3(CurLight->position);
			glm::mat4 matBall(1.0f);


			pDebugSphere->objColour = glm::vec3(1.0f, 1.0f, 1.0f);
			pDebugSphere->setUniformScale(0.1f);			// Position
			DrawObject(pDebugSphere, matBall, program);


			const float ACCURACY_OF_DISTANCE = 0.01f;
			const float INFINITE_DISTANCE = 10000.0f;

			float distance90Percent =
				pLightHelper->calcApproxDistFromAtten(0.90f, ACCURACY_OF_DISTANCE,
					INFINITE_DISTANCE,
					CurLight->atten.x,
					CurLight->atten.y,
					CurLight->atten.z);

			pDebugSphere->setUniformScale(distance90Percent);			// 90% brightness
			pDebugSphere->objColour = glm::vec3(1.0f, 1.0f, 0.0f);
			DrawObject(pDebugSphere, matBall, program);

			pDebugSphere->objColour = glm::vec3(0.0f, 1.0f, 0.0f);	// 50% brightness
			float distance50Percent =
				pLightHelper->calcApproxDistFromAtten(0.50f, ACCURACY_OF_DISTANCE,
					INFINITE_DISTANCE,
					CurLight->atten.x,
					CurLight->atten.y,
					CurLight->atten.z);
			pDebugSphere->setUniformScale(distance50Percent);
			DrawObject(pDebugSphere, matBall, program);

			pDebugSphere->objColour = glm::vec3(1.0f, 0.0f, 0.0f);	// 25% brightness
			float distance25Percent =
				pLightHelper->calcApproxDistFromAtten(0.25f, ACCURACY_OF_DISTANCE,
					INFINITE_DISTANCE,
					CurLight->atten.x,
					CurLight->atten.y,
					CurLight->atten.z);
			pDebugSphere->setUniformScale(distance25Percent);
			DrawObject(pDebugSphere, matBall, program);

			float distance1Percent =
				pLightHelper->calcApproxDistFromAtten(0.01f, ACCURACY_OF_DISTANCE,
					INFINITE_DISTANCE,
					CurLight->atten.x,
					CurLight->atten.y,
					CurLight->atten.z);
			pDebugSphere->objColour = glm::vec3(0.0f, 0.0f, 1.0f);	// 1% brightness
			pDebugSphere->setUniformScale(distance1Percent);
			DrawObject(pDebugSphere, matBall, program);

			pDebugSphere->objColour = oldColour;
			pDebugSphere->nonUniformScale = oldScale;
			pDebugSphere->bIsVisible = false;
		}
	}




		UpdateWindowTitle();

		glfwSwapBuffers(window);		// Shows what we drew

        glfwPollEvents();
		ProcessAsynKeys(window);




    }//while (!glfwWindowShouldClose(window))

	// Delete stuff
	delete pTheShaderManager;
	delete ::g_pTheVAOMeshManager;

	// 
	delete ::g_pDebugRenderer;

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}





void UpdateWindowTitle(void)
{



	return;
}

cMeshObject* findObjectByFriendlyName(std::string theNameToFind)
{
	for ( unsigned int index = 0; index != vec_pObjectsToDraw.size(); index++ )
	{
		// Is this it? 500K - 1M
		// CPU limited Memory delay = 0
		// CPU over powered (x100 x1000) Memory is REAAAAALLY SLOW
		if ( vec_pObjectsToDraw[index]->friendlyName == theNameToFind )
		{
			return vec_pObjectsToDraw[index];
		}
	}

	// Didn't find it.
	return NULL;	// 0 or nullptr
}


cMeshObject* findObjectByUniqueID(unsigned int ID_to_find)
{
	for ( unsigned int index = 0; index != vec_pObjectsToDraw.size(); index++ )
	{
		if ( vec_pObjectsToDraw[index]->getUniqueID() == ID_to_find )
		{
			return vec_pObjectsToDraw[index];
		}
	}

	// Didn't find it.
	return NULL;	// 0 or nullptr
}



