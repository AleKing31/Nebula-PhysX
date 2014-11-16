/*
#include <neb/net/server.hh>

#include <neb/gfx/Context/Base.hh>
#include <neb/gfx/camera/view/ridealong.hh>

#include <neb/debug.hh>
#include <neb/util/decl.hpp>
#include <neb/app/Base.hh>
//#include <neb/Physics.hh>
//#include <neb/simulation_callback.hh>

#include <neb/core/actor/util/Types.hh>
//#include <neb/core/actor/Control/util/Types.hh>
#include <neb/core/actor/RigidBody/Base.hh>
#include <neb/core/actor/RigidDynamic/Local.hh>

#include <neb/network/Types.hh>
#include <neb/network/message.hh>
#include <neb/message/Actor/Control.hh>
#include <neb/message/Types.hh>
*/
#include <gal/log/log.hpp>

#include <neb/core/util/debug.hpp>

//#include <neb/gfx/window/Base.hh>

#include <neb/core/input/signals.hpp>

#include <neb/phx/util/convert.hpp>
#include <neb/phx/util/log.hpp>
#include <neb/phx/core/scene/base.hpp>
#include <neb/phx/core/actor/util/parent.hpp>
#include <neb/phx/core/actor/rigidbody/base.hpp>
#include <neb/phx/core/actor/control/rigidbody/base.hpp>


neb::phx::core::actor::rigidbody::base::base():
	force_(0.0,0.0,0.0),
	torque_(0.0,0.0,0.0)
{
}
void			neb::phx::core::actor::rigidbody::base::add_force(double time) {

	LOG(lg, neb::phx::core::actor::sl, debug) << __PRETTY_FUNCTION__;;

	// body frame
	glm::vec3 f_body;
	glm::vec3 t_body;

	// global frame
	glm::vec3 f_global;
	glm::vec3 t_global;
	
	if(control_) {
		f_body += control_->f_body();
		t_body += control_->t_body();

		f_global += control_->f_global();
		t_global += control_->t_global();
	}

	
	// combine
	f_global += pose_.rot_ * f_body;
	t_global += pose_.rot_ * t_body;

	//physx::PxTransform pose = pose_;
	
	
	assert(px_actor_);
	physx::PxRigidBody* pxrigidbody = px_actor_->isRigidBody();
	assert(pxrigidbody);


	LOG(lg, neb::phx::core::actor::sl, debug)
		<< ::std::setw(8) << "f_global"
		<< ::std::setw(8) << f_global.x
		<< ::std::setw(8) << f_global.y
		<< ::std::setw(8) << f_global.z
		<< " mass " << pxrigidbody->getMass();


	
	pxrigidbody->addForce(phx::util::convert(f_global));
	pxrigidbody->addTorque(phx::util::convert(t_global));
}
void			neb::phx::core::actor::rigidbody::base::createControlManual(std::shared_ptr<neb::core::input::source> src)
{
	LOG(lg, neb::phx::core::actor::sl, info) << __PRETTY_FUNCTION__;

	typedef neb::phx::core::actor::control::rigidbody::manual Control;

	std::shared_ptr<Control> control(new Control());

	control_ = control;

	control->actor_ = isPxActorRigidBodyBase();

	control->connectKeyFun(src, 20);

/*	control->conn_.key_fun_ = window->sig_.key_fun_.connect(
			20,
			neb::gfx::window::signals::KeyFun::slot_type(
				&neb::phx::core::actor::control::rigidbody::base::key_fun,
				control.get(),
				_1,
				_2,
				_3,
				_4,
				_5
				).track_foreign(control)
			);
*/

}
void			neb::phx::core::actor::rigidbody::base::createControlPD()
{
	LOG(lg, neb::phx::core::actor::sl, info) << __PRETTY_FUNCTION__;;
	
	auto self = std::dynamic_pointer_cast<neb::phx::core::actor::rigidbody::base>(
			shared_from_this()
			);
	
	auto control = std::make_shared<neb::phx::core::actor::control::rigidbody::pd>();
	
	control_ = control;
	
	control->actor_ = self;
	
	control->p_target_ = glm::vec3(0,0,5);
	
	control->q_target_ = glm::angleAxis(1.5f, glm::vec3(0.0,1.0,0.0));

}
void		neb::phx::core::actor::rigidbody::base::step(gal::etc::timestep const & ts)
{
	LOG(lg, neb::phx::core::actor::sl, debug) << __PRETTY_FUNCTION__;;

	if(control_) {
		control_->step(ts);
	}

	add_force(ts.dt);
}



