
#include <PxPhysicsAPI.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>

#include <neb/gfx/util/io.hpp>

#include <neb/phx/app/base.hpp>

physx::PxConvexMeshGeometry	frustrum_geometry(glm::mat4 proj) {
	
	auto app = neb::phx::app::base::global();

	glm::vec4 gverts[8] = {
		glm::vec4( 1, 1, 1,1),
		glm::vec4( 1, 1,-1,1),
		glm::vec4( 1,-1, 1,1),
		glm::vec4( 1,-1,-1,1),
		glm::vec4(-1, 1, 1,1),
		glm::vec4(-1, 1,-1,1),
		glm::vec4(-1,-1, 1,1),
		glm::vec4(-1,-1,-1,1)};
	
	physx::PxVec3 verts[8];

	for(int c = 0; c < 8; c++)
	{
		//gverts[c] = glm::affineInverse(proj) * gverts[c];
		gverts[c] = glm::inverseTranspose(proj) * gverts[c];
		gverts[c] = gverts[c] / gverts[c].w;
		verts[c] = physx::PxVec3(
				gverts[c].x,
				gverts[c].y,
				gverts[c].z);

		std::cout << gverts[c] << std::endl;
	}

	physx::PxConvexMeshDesc convexDesc;
	convexDesc.points.count     = 8;
	convexDesc.points.stride    = sizeof(physx::PxVec3);
	convexDesc.points.data      = verts;
	convexDesc.flags            = physx::PxConvexFlag::eCOMPUTE_CONVEX;
	convexDesc.vertexLimit      = 256;
	
	//PxToolkit::MemoryOutputStream buf;
	physx::PxDefaultMemoryOutputStream buf;
	if(!app->px_cooking_->cookConvexMesh(convexDesc, buf))
		    abort();

	physx::PxDefaultMemoryInputData input(buf.getData(), buf.getSize());

	physx::PxConvexMesh* convexMesh = app->px_physics_->createConvexMesh(input);

	physx::PxConvexMeshGeometry g(convexMesh);

	assert(g.isValid());

	auto b = convexMesh->getLocalBounds();
	
	std::cout << "convex mesh" << std::endl;
	std::cout << b.getExtents(0) << std::endl;
	std::cout << b.getExtents(1) << std::endl;
	std::cout << b.getExtents(2) << std::endl;


	//delete convexMesh;

	return g;
}
bool	query(physx::PxConvexMeshGeometry& g0, glm::mat4 v0, physx::PxConvexMeshGeometry& g1, glm::mat4 v1)
{
	assert(g0.isValid());
	assert(g1.isValid());

	physx::PxTransform t0(physx::PxMat44((float*)&v0[0][0]));
	physx::PxTransform t1(physx::PxMat44((float*)&v1[0][0]));

	return physx::PxGeometryQuery::overlap(g0, t0, g1, t1);
	
}



