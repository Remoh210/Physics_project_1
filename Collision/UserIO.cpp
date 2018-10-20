#include "globalOpenGLStuff.h"

#include "globalStuff.h"
//#include <vector>
#include <iostream>

int index = 0;
// This has all the keyboard, mouse, and controller stuff
float lastX;
float lastY;

float pitch;
float yaw;

extern sLight* pTheOneLight;	//  = NULL;
extern cLightManager* LightManager;
int lightIndex = 0;
bool firstMouse = true;

cMeshObject* closedModel;

bool IsPicked = false;
cMeshObject* CloseToObj(std::vector<cMeshObject*> models);

void key_callback( GLFWwindow* window, 
						  int key, 
						  int scancode, 
						  int action, 
						  int mods)
{

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
        glfwSetWindowShouldClose(window, GLFW_TRUE);
	}

	//SAVE MODELS
	if (key == GLFW_KEY_G && action == GLFW_PRESS)
	{
		saveModelInfo("Models.txt", vec_pObjectsToDraw);
		saveLightInfo("lights.txt", LightManager->vecLights);
	}

	//LOAD MODELS
	if (key == GLFW_KEY_H && action == GLFW_PRESS)
	{

	}
	

	if (glfwGetKey(window, GLFW_KEY_K))
	{
		loadModels("models_default.txt", vec_pObjectsToDraw);
		loadLights("ligths_default.txt", LightManager->vecLights);
	}

	if (glfwGetKey(window, GLFW_KEY_L))
	{
		loadModels("Models.txt", vec_pObjectsToDraw);
		loadLights("lights.txt", LightManager->vecLights);
	}


	//Chose the model
	if (key == GLFW_KEY_M && action == GLFW_PRESS)
	{
		if (index < (vec_pObjectsToDraw.size() - 1)) {
			
			index = index + 1;
		}
		else { index = 0; }
		std::cout << "Model " << vec_pObjectsToDraw.at(index)->meshName << "is Chosen" << std::endl;
	}


	//Chose the light
	if (key == GLFW_KEY_N && action == GLFW_PRESS)
	{
		if (lightIndex < (LightManager->vecLights.size() - 1)) {

			lightIndex = lightIndex + 1;
		}
		else { lightIndex = 0; }
		std::cout << "light " << LightManager->vecLights.at(lightIndex)->lightName << "is Chosen" << std::endl;
	}



	//TURN ON The Light

	if (key == GLFW_KEY_9 && action == GLFW_PRESS)
	{
		LightManager->vecLights.at(lightIndex)->param2.x = 1.0f;
	}
	//TURN OFF The Light
	if (key == GLFW_KEY_0 && action == GLFW_PRESS)
	{
		LightManager->vecLights.at(lightIndex)->param2.x = 0.0f;
	}




	if (key == GLFW_KEY_2 && action == GLFW_PRESS)
	{
		vec_pObjectsToDraw.at(index)->bIsUpdatedByPhysics = false;
		std::cout << "Object: " << vec_pObjectsToDraw.at(index)->friendlyName << " physics off";
	}
	if (key == GLFW_KEY_3 && action == GLFW_PRESS)
	{
		vec_pObjectsToDraw.at(index)->bIsUpdatedByPhysics = true;
		std::cout << "Object: " << vec_pObjectsToDraw.at(index)->friendlyName << " physics on";
	}


	//TURN ON AND OFF SPHERES THAT SHOW LIGHT ATTENUATION

	if (glfwGetKey(window, GLFW_KEY_O))
	{	
		LightManager->vecLights.at(lightIndex)->AtenSphere = true;
	}
	if (glfwGetKey(window, GLFW_KEY_P))
	{
		LightManager->vecLights.at(lightIndex)->AtenSphere = false;
	}

	//Shoot
	if (glfwGetKey(window, GLFW_KEY_SPACE))
	{
		cMeshObject* shootSphere = findObjectByFriendlyName("shootBall");
		shootSphere->position = g_CameraEye + glm::vec3(0.0f, 0.0f, 40.0f);
		shootSphere->velocity = Front * 500.0f;
	}

	

	return;
}


void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = SCR_WIDTH / 2.0f;;
		lastY = SCR_HEIGHT / 2.0f;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.05;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;


	//to prevent camera reverse pitch
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	
	Front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	Front.y = sin(glm::radians(pitch));
	Front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(Front);
	Horizontal = glm::normalize(glm::cross(Front, cameraUp));

}


bool IsShiftDown(GLFWwindow* window)
{
	if ( glfwGetKey( window, GLFW_KEY_LEFT_SHIFT ) )	{ return true; }
	if ( glfwGetKey( window, GLFW_KEY_RIGHT_SHIFT ) )	{ return true; }
	// both are up
	return false;
}

bool IsCtrlDown(GLFWwindow* window)
{
	if ( glfwGetKey( window, GLFW_KEY_LEFT_CONTROL ) )	{ return true; }
	if ( glfwGetKey( window, GLFW_KEY_RIGHT_CONTROL ) )	{ return true; }
	// both are up
	return false;
}

bool IsAltDown(GLFWwindow* window)
{
	if ( glfwGetKey( window, GLFW_KEY_LEFT_ALT ) )	{ return true; }
	if ( glfwGetKey( window, GLFW_KEY_RIGHT_ALT ) )	{ return true; }
	// both are up
	return false;
}

bool AreAllModifiersUp(GLFWwindow* window)
{
	if ( IsShiftDown(window) )	{ return false;	}
	if ( IsCtrlDown(window) )	{ return false;	} 
	if ( IsAltDown(window) )	{ return false; }
	// Yup, they are all UP
	return true;
}

void ProcessAsynKeys(GLFWwindow* window)
{
	const float CAMERA_SPEED_SLOW = 5.0f;
	const float CAMERA_SPEED_FAST = 20.0f;

	// WASD + q = "up", e = down		y axis = up and down
	//									x axis = left and right
	//									z axis = forward and backward
	// 

	float cameraSpeed = CAMERA_SPEED_SLOW;
	if ( glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS  )
	{
		cameraSpeed = CAMERA_SPEED_FAST;
	}
	
	// If no keys are down, move the camera
	if ( AreAllModifiersUp(window) )
	{
		// Note: The "== GLFW_PRESS" isn't really needed as it's actually "1" 
		// (so the if() treats the "1" as true...)
	
		if ( glfwGetKey( window, GLFW_KEY_W ) == GLFW_PRESS )
		{
			g_CameraEye.x += cameraSpeed * Front.x;
			g_CameraEye.z += cameraSpeed * Front.z;
			//g_CameraEye.x += Front.x * cameraSpeed;
		}
		if ( glfwGetKey( window, GLFW_KEY_S ) == GLFW_PRESS )	// "backwards"
		{	
			g_CameraEye.x -= cameraSpeed * Front.x;
			g_CameraEye.z -= cameraSpeed * Front.z;
		}
		if ( glfwGetKey( window, GLFW_KEY_A ) == GLFW_PRESS )	// "left"
		{	
			g_CameraEye -= Horizontal * cameraSpeed;
			//g_CameraEye.x -= cameraSpeed;
		}
		if ( glfwGetKey( window, GLFW_KEY_D ) == GLFW_PRESS )	// "right"
		{	
			g_CameraEye += Horizontal * cameraSpeed;
		}
		if ( glfwGetKey( window, GLFW_KEY_Q ) == GLFW_PRESS )	// "up"
		{	
			g_CameraEye.y += cameraSpeed;
		}
		if ( glfwGetKey( window, GLFW_KEY_E ) == GLFW_PRESS )	// "down"
		{	
			g_CameraEye.y -= cameraSpeed;
		}

	}//if(AreAllModifiersUp(window)

	//const float MIN_LIGHT_BRIGHTNESS = 0.001f;

	//LIGHT CONTROL*********************************************************************************************************
	if ( IsCtrlDown(window) )
	{
		
		
		
		if ( glfwGetKey( window, GLFW_KEY_W ) )	{	LightManager->vecLights.at(lightIndex)->position.z += cameraSpeed;	}
		if ( glfwGetKey( window, GLFW_KEY_S ) )	{	LightManager->vecLights.at(lightIndex)->position.z -= cameraSpeed;	}
		if ( glfwGetKey( window, GLFW_KEY_A ) )	{	LightManager->vecLights.at(lightIndex)->position.x -= cameraSpeed;	}
		if ( glfwGetKey( window, GLFW_KEY_D ) ) {	LightManager->vecLights.at(lightIndex)->position.x += cameraSpeed;	}
		if ( glfwGetKey( window, GLFW_KEY_Q ) )	{	LightManager->vecLights.at(lightIndex)->position.y += cameraSpeed;	}
		if ( glfwGetKey( window, GLFW_KEY_E ) )	{	LightManager->vecLights.at(lightIndex)->position.y -= cameraSpeed;	}


		//change colour of the light
		if ( glfwGetKey( window, GLFW_KEY_Z ) )	{   LightManager->vecLights.at(lightIndex)->diffuse = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f); 	}//Red
		if ( glfwGetKey( window, GLFW_KEY_X ) )	{   LightManager->vecLights.at(lightIndex)->diffuse = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);	}//Green
		if ( glfwGetKey( window, GLFW_KEY_C ) )	{   LightManager->vecLights.at(lightIndex)->diffuse = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);    }//Blue
		if ( glfwGetKey( window, GLFW_KEY_V ) )	{	LightManager->vecLights.at(lightIndex)->diffuse = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);	}
		if ( glfwGetKey( window, GLFW_KEY_B ) )	{	LightManager->vecLights.at(lightIndex)->diffuse = glm::vec4(0.0f, 1.0f, 1.0f, 1.0f);	}


		

		//change attenuation:

		//Linear
		if ( glfwGetKey( window, GLFW_KEY_LEFT)  )	{ LightManager->vecLights.at(lightIndex)->atten.y *= 1.05f; }
		if ( glfwGetKey( window, GLFW_KEY_RIGHT) )  { LightManager->vecLights.at(lightIndex)->atten.y *= 0.95f; }

		//Quadratic
		if ( glfwGetKey( window, GLFW_KEY_DOWN) )   { LightManager->vecLights.at(lightIndex)->atten.z *= 0.95f; }
		if ( glfwGetKey( window, GLFW_KEY_UP)   )	{ LightManager->vecLights.at(lightIndex)->atten.z *= 1.05f; }
		

	}

	if (IsShiftDown(window)) 
	{

	}

	//OBJECT CONTROL***********************************************************
	if ( IsAltDown(window) )
	{	//Object Postiton
		if ( glfwGetKey( window, GLFW_KEY_W	) )	{ vec_pObjectsToDraw.at(index)->position.z -= cameraSpeed; }
		if ( glfwGetKey( window, GLFW_KEY_S ) )	{ vec_pObjectsToDraw.at(index)->position.z += cameraSpeed; }
		if ( glfwGetKey( window, GLFW_KEY_A ) )	{ vec_pObjectsToDraw.at(index)->position.x -= cameraSpeed; }
		if ( glfwGetKey( window, GLFW_KEY_D ) ) { vec_pObjectsToDraw.at(index)->position.x += cameraSpeed; }
		if ( glfwGetKey( window, GLFW_KEY_Q ) )	{ vec_pObjectsToDraw.at(index)->position.y -= cameraSpeed; }
		if ( glfwGetKey( window, GLFW_KEY_E ) )	{ vec_pObjectsToDraw.at(index)->position.y += cameraSpeed; }

		//Object Rotation
		if ( glfwGetKey( window, GLFW_KEY_RIGHT ) )	{ vec_pObjectsToDraw.at(index)->postRotation.y += 0.1f; }
		if ( glfwGetKey( window, GLFW_KEY_LEFT ) )	{ vec_pObjectsToDraw.at(index)->postRotation.y -= 0.1f; }
		if ( glfwGetKey( window, GLFW_KEY_UP ) )	{ vec_pObjectsToDraw.at(index)->postRotation.x += 0.1f; }
		if ( glfwGetKey( window, GLFW_KEY_DOWN ) )	{ vec_pObjectsToDraw.at(index)->postRotation.x -= 0.1f; }
		if ( glfwGetKey( window, GLFW_KEY_X ) )		{ vec_pObjectsToDraw.at(index)->postRotation.z += 0.1f; }
		if ( glfwGetKey( window, GLFW_KEY_C ) )		{ vec_pObjectsToDraw.at(index)->postRotation.z -= 0.1f; }

		if (glfwGetKey(window, GLFW_KEY_V)) { vec_pObjectsToDraw.at(index)->nonUniformScale += 0.1f; }
		if (glfwGetKey(window, GLFW_KEY_B)) { vec_pObjectsToDraw.at(index)->nonUniformScale -= 0.1f; }
		//Object Scale

		

	}
	
	return;
}

