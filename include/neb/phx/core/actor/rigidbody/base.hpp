#ifndef __PX_CONTENT_ACTOR_RIGIDBODY_BASE_HPP
#define __PX_CONTENT_ACTOR_RIGIDBODY_BASE_HPP

#include <PxPhysicsAPI.h>

#include <neb/core/pose.hpp>

#include <PhysX/core/actor/rigidactor/base.hpp>
#include <PhysX/core/actor/util/decl.hpp>

namespace neb { namespace phx { namespace core { namespace actor { namespace rigidbody {


	/** @brief base */
	class base:
		virtual public phx::core::actor::rigidactor::base
	{

		public:
			base(sp::shared_ptr<phx::core::actor::util::parent>);

			virtual void					init() = 0;
			virtual void					release() = 0;
			virtual void					step(gal::std::timestep const & ts);


			virtual void					create_physics() = 0;
			virtual void					init_physics() = 0;

			virtual void					add_force(real) = 0;
			virtual void					setPose(neb::core::pose const & pose) = 0;


			void						create_control(sp::shared_ptr<neb::gfx::window::base> window);

			
		public:

			::std::shared_ptr<neb::phx::core::actor::control::rigidbody::base>		control_;


			vec3		force_;
			vec3		torque_;
	};


}}}}}

#endif


