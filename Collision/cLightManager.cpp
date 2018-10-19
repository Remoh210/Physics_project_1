#include "cLightManager.h"


cLightManager::cLightManager()
{
	//intilization stufff
}

void cLightManager::TurnOnLight(int index)
{


}

void cLightManager::LoadUniformLocations(int shaderID)
{
	int i = 0;

	for (std::vector<sLight*>::iterator it = vecLights.begin(); it != vecLights.end(); ++it) 
	{
		vecLights[i]->position_UniLoc = glGetUniformLocation(shaderID, ("theLights[" + std::to_string(i) + "].position").c_str());
		vecLights[i]->diffuse_UniLoc = glGetUniformLocation(shaderID, ("theLights[" + std::to_string(i) + "].diffuse").c_str());
		vecLights[i]->specular_UniLoc = glGetUniformLocation(shaderID, ("theLights[" + std::to_string(i) + "].specular").c_str());
		vecLights[i]->atten_UniLoc = glGetUniformLocation(shaderID, ("theLights[" + std::to_string(i) + "].atten").c_str());
		vecLights[i]->direction_UniLoc = glGetUniformLocation(shaderID, ("theLights[" + std::to_string(i) + "].dirrection").c_str());
		vecLights[i]->param1_UniLoc = glGetUniformLocation(shaderID, ("theLights[" + std::to_string(i) + "].param1").c_str());
		vecLights[i]->param2_UniLoc = glGetUniformLocation(shaderID, ("theLights[" + std::to_string(i) + "].param2").c_str());

		i++;
	}
 }

void cLightManager::CopyLightValuesToShader(void) 
{
	for (std::vector<sLight*>::iterator it = vecLights.begin(); it != vecLights.end(); ++it)
	 {
		sLight* CurLight = *it;
		glUniform4f(CurLight->position_UniLoc,
			CurLight->position.x, CurLight->position.y, CurLight->position.z, 1.0f);
		glUniform4f(CurLight->diffuse_UniLoc,
			CurLight->diffuse.x, CurLight->diffuse.y, CurLight->diffuse.z, 1.0f);
		glUniform4f(CurLight->param2_UniLoc, CurLight->param2.x, 0.0f, 0.0f, 0.0f);	// Turns it "on")
		glUniform4f(CurLight->atten_UniLoc,
			CurLight->atten.x, CurLight->atten.y, CurLight->atten.z, CurLight->atten.w);
	}
}