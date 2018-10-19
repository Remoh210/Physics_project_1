#pragma once

#include "globalOpenGLStuff.h"
#include <glm/glm.hpp>
#include <glm/vec4.hpp>
#include <vector>
#include <string>

struct sLight
{
	glm::vec4 position;			
	glm::vec4 diffuse;		
	glm::vec4 specular;	// rgb = highlight colour, w = power
	glm::vec4 atten;		// x = constant, y = linear, z = quadratic, w = DistanceCutOff
	glm::vec4 direction;	// Spot, directional lights
	glm::vec4 param1;	// x = lightType, y = inner angle, z = outer angle, w = TBD
	glm::vec4 param2;	// x = 0 for off, 1 for on

	// Would set atten.y = newLinAtten
	void SetLinearAttenuation(float newLinAtten);
	void SetPosition( glm::vec3 newPosition );
	void SetSpecularHighlight( glm::vec3 rgbColour, float power );
	// .. and so on

	std::string lightName;

	int position_UniLoc;
	int diffuse_UniLoc;
	int specular_UniLoc;
	int atten_UniLoc;
	int direction_UniLoc;
	int param1_UniLoc;
	int param2_UniLoc;

	bool AtenSphere;
};

class cLightManager
{
public:
	cLightManager();
	// STRONGLY suggest you make something like this... 

	void TurnOnLight(int index);
	void ChangeLightType( std::string lightType, int index );

	std::vector<sLight*> vecLights;

	// Do all the glGetUniformLocation() calls and store them...
	void LoadUniformLocations( int shaderID );

	// This would do the  nasty glUniformXf() calls
	// Start of every frame or scene
	void CopyLightValuesToShader(void);

};


