// PhysicsStuff
#include "globalStuff.h"	// 
#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include "sModelDrawInfo.h"

typedef glm::vec3 Point;
typedef glm::vec3 Vector;

const float GROUND_PLANE_Y = -3.0f;			// Lowest the objects can go
const float ROOF_Y = 350.0f;
const float LIMIT_POS_X = 300.0f;			// Lowest the objects can go
const float LIMIT_NEG_X = -100.0f;			// Lowest the objects can go
const float LIMIT_POS_Z = 300.0f;			// Lowest the objects can go
const float LIMIT_NEG_Z = -300.0f;			// Lowest the objects can go




//class cBox
//{
//public:
//	cPlanes sides[6];
//	float leftSide;
//	float rightSide;
//	//...
//	glm::vec3 minXYZ:
//	glm::vec3 maxXYZ;

//	glm::vec3 facingOutsideVectors[6];
//	// 
//	glm::vec3 centreXYZ;
//	glm::vec3 sideLengths;
//	glm::vec3 halfSideLengths;
//}
bool SphereTraingleTest(cMeshObject* pSphere, cMeshObject* pTriangle);
bool AreSpheresPenetrating(cMeshObject* pA, cMeshObject* pB);
bool SphereBoxCollision(cMeshObject* sphere, cMeshObject* box);
bool TestSphereAABB(cMeshObject* s, cMeshObject* b);
bool TestForCollision(cMeshObject* pA, cMeshObject* pB);


// Called every frame
void DoPhysicsUpdate(double fDeltaTime,
	std::vector< cMeshObject* > &vec_pObjectsToDraw)
{
	float deltaTime = static_cast<float>(fDeltaTime);

	// Make sure it's not tooooooo big
	const float LARGEST_DELTATIME = 1.20f;			// 10 ms = 10 Hz

	if (deltaTime > LARGEST_DELTATIME)
	{
		deltaTime = LARGEST_DELTATIME;
	}//if ( deltaTime

	// Loop through all objects
	for (std::vector< cMeshObject* >::iterator itMesh = vec_pObjectsToDraw.begin();
		itMesh != vec_pObjectsToDraw.end(); itMesh++)
	{
		cMeshObject* pCurMesh = *itMesh;

		if (pCurMesh->bIsUpdatedByPhysics)
		{


			pCurMesh->velocity.x = pCurMesh->velocity.x + (pCurMesh->accel.x * deltaTime);
			pCurMesh->velocity.y = pCurMesh->velocity.y + (pCurMesh->accel.y * deltaTime);
			pCurMesh->velocity.z = pCurMesh->velocity.z + (pCurMesh->accel.z * deltaTime);

			pCurMesh->position.x = pCurMesh->position.x + (pCurMesh->velocity.x * deltaTime);
			pCurMesh->position.y = pCurMesh->position.y + (pCurMesh->velocity.y * deltaTime);
			pCurMesh->position.z = pCurMesh->position.z + (pCurMesh->velocity.z * deltaTime);



			//initial_position

			if (pCurMesh->bRandomGenObj && (glm::distance(pCurMesh->position, pCurMesh->initial_position) > 1500.0f))
			{
				pCurMesh->position = pCurMesh->initial_position;
				pCurMesh->velocity = glm::vec3(getRandBetween0and1<float>() * 200.0f - 5.0f,
					getRandBetween0and1<float>() * 200.0f - 5.0f,
					getRandBetween0and1<float>() * 200.0f - 5.0f);


				pCurMesh->objColour = glm::vec3(getRandBetween0and1<float>() * 1.0f - 0.0f,
					getRandBetween0and1<float>() * 1.0f - 0.0f,
					getRandBetween0and1<float>() * 1.0f - 0.0f);
			}


			//if ( pCurMesh->position.y  <= GROUND_PLANE_Y )
			//{

			//	glm::vec3 normalToGround = glm::vec3( 0.0f, 1.0f, 0.0f );



			//	glm::vec3 newVel = glm::reflect( pCurMesh->velocity, normalToGround );

			//	pCurMesh->velocity = newVel;
			//}

			//	if ( pCurMesh->position.y  >= ROOF_Y)
			//{

			//	glm::vec3 normalToGround = glm::vec3( 0.0f, -1.0f, 0.0f );



			//	glm::vec3 newVel = glm::reflect( pCurMesh->velocity, normalToGround );

			//	pCurMesh->velocity = newVel;
			//}

			//if ( pCurMesh->position.x >= LIMIT_POS_X )
			//{
			//	pCurMesh->velocity.x = -fabs(pCurMesh->velocity.x) ;
			//}
			//if ( pCurMesh->position.x <= LIMIT_NEG_X )
			//{
			//	pCurMesh->velocity.x = fabs(pCurMesh->velocity.x) ;
			//}
			//if ( pCurMesh->position.z >= LIMIT_POS_Z )
			//{
			//	pCurMesh->velocity.z = -fabs(pCurMesh->velocity.z) ;
			//}
			//if ( pCurMesh->position.z <= LIMIT_NEG_Z )
			//{
			//	pCurMesh->velocity.z = fabs(pCurMesh->velocity.z) ;
			//}


		//	// Check if I'm contacting another sphere..
		//	for ( std::vector< cMeshObject* >::iterator itMesh = vec_pObjectsToDraw.begin();
		//		  itMesh != vec_pObjectsToDraw.end(); itMesh++ )
		//	{
		//		cMeshObject* pOtherMesh = *itMesh;
//
		//		if ( ! pOtherMesh->bIsUpdatedByPhysics )
		//		{
		//			// Or do I????? (can non moving things still collide with this???)
		//			continue;
		//		}
//
		//		// Same mesh
		//		if ( pCurMesh != pOtherMesh )
		//		{
		//			if ( AreSpheresPenetrating( pOtherMesh, pCurMesh ) )
		//			{
		//				pCurMesh->objColour = glm::vec3( 1.0f, 0.0f, 0.0f );
		//			}
		//			else
		//			{
		//				// Make it pink
		//			}
		//		}
		//		
//
//
		//	}// Inner sphere-sphere test
//
//
//
		}//if ( pCurMesh
	}//for ( std::vector< cMeshObject*


	// Test for collisions
	for (std::vector< cMeshObject* >::iterator itObjectA = vec_pObjectsToDraw.begin();
		itObjectA != vec_pObjectsToDraw.end(); itObjectA++)
	{
		// Go through all the other objects and test with this one...

		for (std::vector< cMeshObject* >::iterator itObjectB = vec_pObjectsToDraw.begin();
			itObjectB != vec_pObjectsToDraw.end(); itObjectB++)
		{

			cMeshObject* pObjectA = *itObjectA;
			cMeshObject* pObjectB = *itObjectB;
			// Same? 

			if (pObjectA != pObjectB)
			{
				// Do BOTH of these have a "shape" defined
				// Could also test for the enum (which is WAY better)
				if ((pObjectA->pTheShape != NULL) &&
					(pObjectB->pTheShape != NULL))
				{

					if ((pObjectA->shapeType == cMeshObject::SPHERE) && (pObjectB->shapeType == cMeshObject::SPHERE))
					{


						sSphere* sphA = (sSphere*)(pObjectA->pTheShape);
						sSphere* sphB = (sSphere*)(pObjectA->pTheShape);
						if (AreSpheresPenetrating(pObjectA, pObjectB))
						{
							if (glm::length(pObjectA->velocity) < 0.10f)
							{
								pObjectA->velocity = -pObjectB->velocity * 1.2f;
								//pObjectB->velocity = -pObjectB->velocity;
							}
							else if (glm::length(pObjectB->velocity) < 0.10f)
							{
								pObjectB->velocity = -pObjectA->velocity  * 1.2f;
								//pObjectA->velocity = -pObjectA->velocity;
							}
							else
							{
								glm::vec3 AnewVel = glm::reflect(pObjectA->velocity, glm::normalize(pObjectB->velocity));
								glm::vec3 BnewVel = glm::reflect(pObjectB->velocity, glm::normalize(pObjectA->velocity));

								pObjectA->velocity = AnewVel;
								pObjectB->velocity = BnewVel;

								pObjectA->objColour = pObjectB->objColour;

							}
						}

					}

					else if ((pObjectA->shapeType == cMeshObject::SPHERE) && (pObjectB->shapeType == cMeshObject::MESH))
					{
						sModelDrawInfo modelInfo;
						std::vector<sClosestPointData> closestPoints;
						g_pTheVAOMeshManager->FindDrawInfoByModelName(pObjectB->meshName, modelInfo);
						CalculateClosestPointsOnMesh(modelInfo, pObjectA->position, closestPoints, pObjectB->position);

						if (closestPoints.size() != 0)
						{
							float minDistance = glm::distance(pObjectA->position, closestPoints[0].thePoint);
							unsigned int minTriangleIndex = closestPoints[0].triangleIndex;
							for (unsigned int triIndex = 0; triIndex != closestPoints.size(); triIndex++)
							{

								float curDist = glm::distance(pObjectA->position, closestPoints[triIndex].thePoint);

								if (curDist < minDistance)
								{
									minDistance = curDist;
									minTriangleIndex = closestPoints[triIndex].triangleIndex;
								}
								sSphere* Sphere = (sSphere*)(pObjectA->pTheShape);
								if (minDistance < Sphere->radius) {


									glm::vec3 vert1 = glm::vec3(modelInfo.pVerticesFromFile[modelInfo.pTriangles[minTriangleIndex].vertex_index_1].x,
										modelInfo.pVerticesFromFile[modelInfo.pTriangles[minTriangleIndex].vertex_index_1].y,
										modelInfo.pVerticesFromFile[modelInfo.pTriangles[minTriangleIndex].vertex_index_1].z) + pObjectB->position;
									glm::vec3 vert2 = glm::vec3(
										modelInfo.pVerticesFromFile[modelInfo.pTriangles[minTriangleIndex].vertex_index_2].x,
										modelInfo.pVerticesFromFile[modelInfo.pTriangles[minTriangleIndex].vertex_index_2].y,
										modelInfo.pVerticesFromFile[modelInfo.pTriangles[minTriangleIndex].vertex_index_2].z) + pObjectB->position;
									glm::vec3 vert3 = glm::vec3(
										modelInfo.pVerticesFromFile[modelInfo.pTriangles[minTriangleIndex].vertex_index_3].x,
										modelInfo.pVerticesFromFile[modelInfo.pTriangles[minTriangleIndex].vertex_index_3].y,
										modelInfo.pVerticesFromFile[modelInfo.pTriangles[minTriangleIndex].vertex_index_3].z) + pObjectB->position;


									glm::vec3 normal = glm::cross(
										vert2 - vert1,
										vert3 - vert1
									);
									normal = glm::normalize(normal);


									glm::vec3 newVel = glm::reflect(pObjectA->velocity, normal);

									pObjectA->velocity = newVel;



								}
							}

						}
					}//else if 

					else if ((pObjectA->shapeType == cMeshObject::SPHERE) && (pObjectB->shapeType == cMeshObject::AABB))
					{

						if (SphereBoxCollision(pObjectA, pObjectB))
						{

							pObjectA->objColour = pObjectB->objColour;
							pObjectA->velocity = -pObjectA->velocity;



							//g_pDebugRenderer->addLine(pObjectA->position, pObjectB->position, glm::vec3(1.0f, 1.0f, 0.0f), 3.0f);
						}
					}
				}
			}//if(pObjectA != pObjectB)
		}// inner loop
	}// outer loop


	return;
}


Point ClosestPtPointTriangle(Point p, Point a, Point b, Point c)
{
	Vector ab = b - a;
	Vector ac = c - a;
	Vector bc = c - b;

	// Compute parametric position s for projection P' of P on AB,
	// P' = A + s*AB, s = snom/(snom+sdenom)
 //   float snom = Dot(p - a, ab), sdenom = Dot(p - b, a - b);
	float snom = glm::dot(p - a, ab);
	float sdenom = glm::dot(p - b, a - b);

	// Compute parametric position t for projection P' of P on AC,
	// P' = A + t*AC, s = tnom/(tnom+tdenom)
//    float tnom = Dot(p - a, ac), tdenom = Dot(p - c, a - c);
	float tnom = glm::dot(p - a, ac);
	float tdenom = glm::dot(p - c, a - c);

	if (snom <= 0.0f && tnom <= 0.0f) return a; // Vertex region early out

	// Compute parametric position u for projection P' of P on BC,
	// P' = B + u*BC, u = unom/(unom+udenom)
//    float unom = Dot(p - b, bc), udenom = Dot(p - c, b - c);
	float unom = glm::dot(p - b, bc);
	float udenom = glm::dot(p - c, b - c);

	if (sdenom <= 0.0f && unom <= 0.0f) return b; // Vertex region early out
	if (tdenom <= 0.0f && udenom <= 0.0f) return c; // Vertex region early out


	// P is outside (or on) AB if the triple scalar product [N PA PB] <= 0
//    Vector n = Cross(b - a, c - a);
	Vector n = glm::cross(b - a, c - a);
	//    float vc = Dot(n, Cross(a - p, b - p));

	float vc = glm::dot(n, glm::cross(a - p, b - p));

	// If P outside AB and within feature region of AB,
	// return projection of P onto AB
	if (vc <= 0.0f && snom >= 0.0f && sdenom >= 0.0f)
		return a + snom / (snom + sdenom) * ab;

	// P is outside (or on) BC if the triple scalar product [N PB PC] <= 0
//    float va = Dot(n, Cross(b - p, c - p));
	float va = glm::dot(n, glm::cross(b - p, c - p));


	// If P outside BC and within feature region of BC,
	// return projection of P onto BC
	if (va <= 0.0f && unom >= 0.0f && udenom >= 0.0f)
		return b + unom / (unom + udenom) * bc;

	// P is outside (or on) CA if the triple scalar product [N PC PA] <= 0
//    float vb = Dot(n, Cross(c - p, a - p));
	float vb = glm::dot(n, glm::cross(c - p, a - p));

	// If P outside CA and within feature region of CA,
	 // return projection of P onto CA
	if (vb <= 0.0f && tnom >= 0.0f && tdenom >= 0.0f)
		return a + tnom / (tnom + tdenom) * ac;

	// P must project inside face region. Compute Q using barycentric coordinates
	float u = va / (va + vb + vc);
	float v = vb / (va + vb + vc);
	float w = 1.0f - u - v; // = vc / (va + vb + vc)
	return u * a + v * b + w * c;
}

// Pass in the terrain
// Pass in the location of the Bunny (the one I can move)
// "return" (by reference) as list of points
// --> then I can draw those points

void CalculateClosestPointsOnMesh(sModelDrawInfo theMeshDrawInfo,
	glm::vec3 pointToTest,
	std::vector<sClosestPointData> &vecPoints, glm::vec3 objPos)
{
	vecPoints.clear();

	// For each triangle in the mesh information...
	for (unsigned int triIndex = 0; triIndex != theMeshDrawInfo.numberOfTriangles; triIndex++)
	{
		sPlyTriangle CurTri = theMeshDrawInfo.pTriangles[triIndex];

		sClosestPointData closestTri;
		closestTri.triangleIndex = triIndex;

		// ... call the ClosestPointToTriangle...
		// Need to get the 3 vertices of the triangle
		sPlyVertex corner_1 = theMeshDrawInfo.pVerticesFromFile[CurTri.vertex_index_1];
		sPlyVertex corner_2 = theMeshDrawInfo.pVerticesFromFile[CurTri.vertex_index_2];
		sPlyVertex corner_3 = theMeshDrawInfo.pVerticesFromFile[CurTri.vertex_index_3];

		// Convert this to glm::vec3
		glm::vec3 vert_1 = glm::vec3(corner_1.x, corner_1.y, corner_1.z) + objPos;
		glm::vec3 vert_2 = glm::vec3(corner_2.x, corner_2.y, corner_2.z) + objPos;
		glm::vec3 vert_3 = glm::vec3(corner_3.x, corner_3.y, corner_3.z) + objPos;

		closestTri.thePoint = ClosestPtPointTriangle(pointToTest, vert_1, vert_2, vert_3);

		vecPoints.push_back(closestTri);

		// ...and push back the restulting point
	}//for ( unsigned int triIndex = 0




}



bool AreSpheresPenetrating(cMeshObject* pA, cMeshObject* pB)
{
	sSphere* pSphereA = (sSphere*)(pA->pTheShape);
	sSphere* pSphereB = (sSphere*)(pB->pTheShape);

	if (glm::distance(pA->position, pB->position) < (pSphereA->radius + pSphereB->radius))
	{
		// Yup
		return true;
	}
	// Nope 
	return false;
}
float SqDistPointAABB(Point p, cMeshObject* obj)
{
	sAABB* pAABB = (sAABB*)(obj->pTheShape);

	float sqDist = 0.0f;
	for (int i = 0; i < 3; i++) {
		// for each axis count any excess distance outside box extents
		float v = p[i];
		if (v < pAABB->minXYZ[i]) sqDist += (pAABB->minXYZ[i] - v) * (pAABB->minXYZ[i] - v);
		if (v > pAABB->maxXYZ[i]) sqDist += (v - pAABB->maxXYZ[i]) * (v - pAABB->maxXYZ[i]);
	}
	return sqDist;
}


// Returns true if sphere s intersects AABB b, false otherwise
bool TestSphereAABB(cMeshObject* s, cMeshObject* b)
{
	sSphere* sphere = (sSphere*)(b->pTheShape);
	// Compute squared distance between sphere center and AABB
	// the sqrt(dist) is fine to use as well, but this is faster.
	float sqDist = SqDistPointAABB(s->position, b);

	// Sphere and AABB intersect if the (squared) distance between them is
	// less than the (squared) sphere radius.
	return sqDist <= sphere->radius * sphere->radius;
}

bool SphereTraingleTest(cMeshObject* pSphere, cMeshObject* pTriangle)
{
	sSphere* pSphereA = (sSphere*)(pSphere->pTheShape);
	sTriangle* pTri = (sTriangle*)(pTriangle->pTheShape);

	glm::vec3 closestPointToTri = ClosestPtPointTriangle(pSphere->position,
		pTri->v[0], pTri->v[1], pTri->v[2]);

	// is this point LESS THAN the radius of the sphere? 
	if (glm::distance(closestPointToTri, pSphere->position) <= pSphereA->radius)
	{
		return true;
	}

	return false;
}

bool TestForCollision(cMeshObject* pA, cMeshObject* pB)
{
	if (pA->pTheShape == NULL) { return false; /*print error?*/ }
	if (pB->pTheShape == NULL) { return false; /*print error?*/ }

	// Sphere - sphere
	if ((pA->shapeType == cMeshObject::SPHERE) &&
		(pB->shapeType == cMeshObject::SPHERE))
	{
		return AreSpheresPenetrating(pA, pB);
	}
	else if ((pA->shapeType == cMeshObject::SPHERE) &&
		(pB->shapeType == cMeshObject::TRIANGLE))
	{
		return SphereTraingleTest(pA, pB);
	}
	//else


	return false;
}



bool SphereBoxCollision(cMeshObject* sphere, cMeshObject* box)
{
	sSphere* sSp = (sSphere*)(sphere->pTheShape);
	sAABB* sBox = (sAABB*)(box->pTheShape);


	float sphereXDistance = abs(sphere->position.x - box->position.x);
	float sphereYDistance = abs(sphere->position.y - box->position.y);
	float sphereZDistance = abs(sphere->position.z - box->position.z);

	if (sphereXDistance >= (sBox->sizeXYZ.x + sSp->radius))
	{
		return false;
	}
	if (sphereYDistance >= (sBox->sizeXYZ.y + sSp->radius))
	{
		return false;
	}
	if (sphereZDistance >= (sBox->sizeXYZ.z + sSp->radius))
	{
		return false;
	}


	if (sphereXDistance < (sBox->sizeXYZ.x))
	{
		return true;
	}
	if (sphereYDistance < (sBox->sizeXYZ.y))
	{
		return true;
	}
	if (sphereZDistance < (sBox->sizeXYZ.z))
	{
		return true;
	}

	float distance_sq = ((sphereXDistance - sBox->sizeXYZ.x) * (sphereXDistance - sBox->sizeXYZ.x)) +
		((sphereYDistance - sBox->sizeXYZ.y) * (sphereYDistance - sBox->sizeXYZ.y) +
		((sphereYDistance - sBox->sizeXYZ.z) * (sphereYDistance - sBox->sizeXYZ.y)));

	return (distance_sq < (sSp->radius * sSp->radius));
}





