#include <gal/log/log.hpp>

#include <neb/core/debug.hh>
#include <neb/core/shape/base.hpp>

#include <neb/phx/app/base.hpp>
#include <neb/phx/util/convert.hpp>
#include <neb/phx/util/log.hpp>
#include <neb/phx/core/actor/util/parent.hpp>
#include <neb/phx/core/actor/rigidstatic/base.hpp>
#include <neb/phx/core/scene/base.hpp>

neb::phx::core::actor::rigidstatic::base::base(sp::shared_ptr<neb::phx::core::actor::util::parent> parent):
	neb::core::actor::base(parent),
	neb::phx::core::actor::base(parent),
	neb::phx::core::actor::actor::base(parent),
	neb::phx::core::actor::rigidactor::base(parent)
{
	if(DEBUG_NEB) LOG(lg, neb::phx::core::actor::sl, debug) << __PRETTY_FUNCTION__;
}
void			neb::phx::core::actor::rigidstatic::base::create_physics() {
	if(DEBUG_NEB) LOG(lg, neb::phx::core::actor::sl, debug) << __PRETTY_FUNCTION__;
	
	if(px_actor_ != NULL) {
		if(DEBUG_NEB) LOG(lg, neb::phx::core::actor::sl, debug) << "been here!";
		return;
	}
	
	auto scene = sp::dynamic_pointer_cast<phx::core::scene::base>(getScene());//scene_.lock();
	assert(scene);
	
	auto p = getPose();

	physx::PxTransform pose(
			neb::phx::util::convert(vec3(p.pos_)),
			neb::phx::util::convert(p.rot_)
			);

	//pose.p.print();
	//pose.q.print();

	// PxActor
	auto app = neb::phx::app::base::global();
	auto pxph = app->px_physics_;
	assert(pxph);
	physx::PxRigidStatic* px_rigid_static = pxph->createRigidStatic(pose);

	if(px_rigid_static == NULL) {
		printf("create actor failed!");
		exit(1);
	}

	px_actor_ = px_rigid_static;

	// userData
	px_rigid_static->userData = isActorBase().get();
	assert(this == shared_from_this().get());
	assert(this == isActorBase().get());

	// add PxActor to PxScene
	assert(scene->px_scene_ != NULL);

	scene->px_scene_->addActor(*px_rigid_static);
}
void			neb::phx::core::actor::rigidstatic::base::init_physics() {

	printf("%s\n", __PRETTY_FUNCTION__);

	setupFiltering();
}


