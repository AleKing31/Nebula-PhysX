#include <gal/log/log.hpp>

#include <neb/fnd/util/debug.hpp>

#include <neb/phx/util/convert.hpp>
#include <neb/phx/core/actor/util/parent.hpp>
#include <neb/phx/core/actor/rigidactor/base.hpp>

//#include <neb/phx/core/shape/box.hpp>
typedef neb::phx::core::actor::rigidactor::base THIS;
//neb::fnd::actor::rigidactor::base::base() {
//}
/*neb::phx::core::actor::rigidactor::base::base(std::shared_ptr<neb::phx::core::actor::util::parent> parent):
	neb::fnd::core::actor::base(parent),
	neb::phx::core::actor::base(parent),
	neb::phx::core::actor::actor::base(parent)
{
}*/
void		THIS::setupFiltering()
{
	std::cout << __PRETTY_FUNCTION__ << this << std::endl;

	auto p = getParent();

	assert(px_actor_);
	physx::PxRigidActor* actor = (physx::PxRigidActor*)px_actor_->isRigidActor();
	assert(actor);


	// copy actor's filter data into PhysX objects

	physx::PxFilterData coll_data;
	coll_data.word0 = p->simulation_.word0;
	coll_data.word1 = p->simulation_.word1;
	coll_data.word2 = p->simulation_.word2;
	coll_data.word3 = p->simulation_.word3;

	physx::PxFilterData sq_data;
	sq_data.word0 = p->scene_query_.word0;
	sq_data.word1 = p->scene_query_.word1;
	sq_data.word2 = p->scene_query_.word2;
	sq_data.word3 = p->scene_query_.word3;

	// apply that data to each shape

	const physx::PxU32 numShapes = actor->getNbShapes();
	
	physx::PxShape** shapes = new physx::PxShape*[numShapes];
	
	std::cout << numShapes << std::endl;

	actor->getShapes(shapes, numShapes);

	for(physx::PxU32 i = 0; i < numShapes; i++)
	{
		physx::PxShape* shape = shapes[i];
		shape->setSimulationFilterData(coll_data);
		shape->setQueryFilterData(sq_data);
	}

	delete[] shapes;
}
void		THIS::set_pose_global(gal::math::pose const & pose)
{
	auto p = getParent();

	/** @todo if is nested actor, then this is wrong... */
	p->pose_ = pose;
	
	assert(px_actor_);
	auto px_rigidactor = px_actor_->isRigidActor();
	assert(px_rigidactor);

	px_rigidactor->setGlobalPose(neb::phx::util::convert_pose(pose));
}





