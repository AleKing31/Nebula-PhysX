#include <Galaxy-Log/log.hpp>
#include <neb/core/debug.hh>

#include <neb/phx/core/actor/rigidbody/base.hpp>
#include <neb/phx/core/actor/control/rigidbody/base.hpp>
#include <neb/phx/game/ai/base.hpp>

void						neb::phx::game::ai::base::step(gal::std::timestep const & ts) {

	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "phx game", debug) << __PRETTY_FUNCTION__;

	auto actor = sp::dynamic_pointer_cast<neb::phx::core::actor::rigidbody::base>(actor_.lock());
	if(!actor) return;

	auto target = target_.lock();
	if(!target) return;
	
	auto control = actor->control_;
	if(!control) return;

	auto pd = sp::dynamic_pointer_cast<neb::phx::core::actor::control::rigidbody::pd>(control);

	if(!pd) return;
	
	
	
	vec3 look = vec3(target->pose_.pos_ - actor->pose_.pos_);
	vec3 up(0,0,-1);
	
	look = glm::normalize(look);
	
	float w = glm::dot(up,look);

	vec3 v = glm::cross(up,look);
	//vec3 v = glm::cross(look,up);
	
	quat q(1.0 + w, v.x, v.y, v.z);
	q = glm::normalize(q);
	
	//quat q(up,look);
	
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "phx game", debug)
		<< ::std::setw(16) << "look"
		<< ::std::setw(16) << look.x
		<< ::std::setw(16) << look.y
		<< ::std::setw(16) << look.z;

	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "phx game", debug)
		<< ::std::setw(16) << "q"
		<< ::std::setw(16) << q.w
		<< ::std::setw(16) << q.x
		<< ::std::setw(16) << q.y
		<< ::std::setw(16) << q.z;

	//if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "phx game", debug) << __PRETTY_FUNCTION__;

	pd->q_target_ = q;
	
	
	// fire
	if(glm::length(pd->getOrientationError()) < 0.1) {
		// find any weapon
		auto it = actor->neb::phx::game::weapon::util::parent::map_.begin();
		if(it != actor->neb::phx::game::weapon::util::parent::map_.end()) {
			auto weap = it->ptr_;
			if(weap) {
				weap->fire();
			}
		}
	}

}




