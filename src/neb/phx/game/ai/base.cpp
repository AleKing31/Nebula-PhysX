
#include <neb/fnd/util/debug.hpp>
#include <neb/fnd/game/ai/base.hpp>
#include <neb/fnd/core/actor/rigidbody/Base.hpp>

#include <neb/fnd/core/actor/control/rigidbody/PD.hpp>


typedef neb::fnd::game::ai::base THIS;

void			THIS::step(gal::etc::timestep const & ts)
{
	printv_func(DEBUG);

	//auto actor = std::dynamic_pointer_cast<neb::phx::core::actor::rigidbody::base>(actor_.lock());
	auto actor = std::dynamic_pointer_cast<neb::fnd::core::actor::rigidbody::base>(actor_.lock());
	
	if(!actor) return;

	auto target = target_.lock();
	if(!target) return;
	
	auto control = actor->control_;
	if(!control) return;

	auto pd = std::dynamic_pointer_cast<neb::fnd::core::actor::control::rigidbody::PD>(control);

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
	
	printv(DEBUG, "look %16f%16f%16f\n",
		look.x,
		look.y,
		look.z);

	printv(DEBUG, "q    %16f%16f%16f\n",
		q.w,
		q.x,
		q.y,
		q.z);

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




