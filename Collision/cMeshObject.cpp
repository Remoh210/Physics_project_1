#include "cMeshObject.h"

cMeshObject::cMeshObject() 
{
	this->preRotation = glm::vec3(0.0f);
	this->position = glm::vec3(0.0f);
	this->postRotation = glm::vec3(0.0f);
	this->nonUniformScale = glm::vec3(1.0f);
	// 
	this->bIsVisible = true;
	this->bIsWireFrame = false;

	// Set unique ID
	this->m_uniqueID = cMeshObject::m_NextID;
	// Increment
	cMeshObject::m_NextID++;	// 32 bit - 4 billion

	this->objColour = glm::vec3(1.0f, 1.0f, 1.0f);	// white by default
	this->bUseVertexColour = false;

	this->bDontLight = false;
	this->initial_position = glm::vec3(0.0f);
	this->bRandomGenObj = false;
	this->velocity = glm::vec3(0.0f);
	this->accel = glm::vec3(0.0f);
	this->bIsUpdatedByPhysics = false;	// physics ignores by default

//	this->radius = 0.0f;

	this->pDebugRenderer = NULL;

	// Set shape to NULL
	this->pTheShape = NULL;
	this->shapeType = cMeshObject::UNKOWN_SHAPE;

	return;
}

void cMeshObject::setUniformScale(float scale)
{
	this->nonUniformScale = glm::vec3(scale,scale,scale);
	return;
}
	
//static unsigned int m_NextID; //= 0;

//static 
unsigned int cMeshObject::m_NextID = cMeshObject::STARTING_ID_VALUE;


void cMeshObject::Update(double deltaTime)
{
	if ( this->bIsUpdatedByPhysics )
	{
		// Figure out a line showing the velocity
		glm::vec3 vVel = this->velocity + this->position;
		glm::vec3 vAcc = this->accel + this->position;

		if ( this->pDebugRenderer )		// != NULL
		{
			this->pDebugRenderer->addLine( this->position, vVel, 
										   glm::vec3( 0.0f, 1.0f, 0.0f ), 0.0f );

			this->pDebugRenderer->addLine( this->position, vAcc, 
										   glm::vec3( 0.0f, 1.0f, 1.0f ), 0.0f );
		}//if ( this->pDebugRenderer )	
	}//if ( this->bIsUpdatedByPhysics )

	return;
}
