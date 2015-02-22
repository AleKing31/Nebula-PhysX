
#include <neb/fnd/util/debug.hpp>

#include <neb/phx/core/actor/rigidbody/base.hpp>
#include <neb/phx/core/actor/control/rigidbody/base.hpp>
#include <neb/fnd/game/ai/base.hpp>
#include <neb/fnd/util/log.hpp>



void						neb::fnd::game::ai::base::step(gal::etc::timestep const & ts) {

	LOG(lg, neb::fnd::sl, debug) << __PRETTY_FUNCTION__;

	auto actor = std::dynamic_pointer_cast<neb::phx::core::actor::rigidbody::base>(actor_.lock());
	//auto actor = std::dynamic_pointer_cast<neb::fnd::core::actor::base>(actor_.lock());
	if(!actor) return;

	auto target = target_.lock();
	if(!target) return;
	
	auto control = actor->control_;
	if(!control) return;

	auto pd = std::dynamic_pointer_cast<neb::phx::core::actor::control::rigidbody::pd>(control);

	if(!pd) return;
	
	
	
	glm::vec3 look = glm::vec3(target->pose_.pos_ - actor->pose_.pos_);
	glm::vec3 up(0,0,-1);
	
	look = glm::normalize(look);
	
	float w = glm::dot(up,look);

	glm::vec3 v = glm::cross(up,look);
	//vec3 v = glm::cross(look,up);
	
	glm::quat q(1.0 + w, v.x, v.y, v.z);
	q = glm::normalize(q);
	
	//quat q(up,look);
	
	LOG(lg, neb::fnd::sl, debug)
		<< ::std::setw(16) << "look"
		<< ::std::setw(16) << look.x
		<< ::std::setw(16) << look.y
		<< ::std::setw(16) << look.z;

	LOG(lg, neb::fnd::sl, debug)
		<< ::std::setw(16) << "q"
		<< ::std::setw(16) << q.w
		<< ::std::setw(16) << q.x
		<< ::std::setw(16) << q.y
		<< ::std::setw(16) << q.z;

	//LOG(lg, neb::fnd::sl, debug) << __PRETTY_FUNCTION__;

	pd->q_target_ = q;
	
	typedef neb::fnd::game::weapon::util::parent W;

	// fire
	if(glm::length(pd->getOrientationError()) < 0.1) {
		// find any weapon
		auto weap = actor->W::map_.front();
		if(weap) {
			weap->fire();
		}
	}

}




