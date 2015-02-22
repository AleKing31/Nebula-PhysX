#ifndef __PX_CONTENT_ACTOR_RIGIDBODY_BASE_HPP
#define __PX_CONTENT_ACTOR_RIGIDBODY_BASE_HPP

#include <PxPhysicsAPI.h>

#include <neb/fnd/itf/verbosity.hpp>
#include <neb/fnd/math/pose.hpp>

#include <neb/phx/core/actor/rigidactor/base.hpp>
#include <neb/phx/core/actor/util/decl.hpp>

namespace neb { namespace phx { namespace core { namespace actor { namespace rigidbody {
	/** @brief base */
	class base:
		public neb::fnd::itf::verbosity<neb::phx::core::actor::rigidbody::base>,
		virtual public neb::phx::core::actor::rigidactor::base
	{
		public:
			using neb::fnd::itf::verbosity<neb::phx::core::actor::rigidbody::base>::printv;
			typedef shared_ptr<neb::phx::core::actor::control::rigidbody::base>	control_shared;
			base();
			//virtual void					init() = 0;
			//virtual void					release() = 0;
			virtual void					step(gal::etc::timestep const & ts);
			/** @brief create physics
			 *
			 * @note implemented by rigidstatic and rigiddynamic
			 */
			virtual void					create_physics() = 0;
			/** @brief initialize physics
			 *
			 * @note implemented by rigidstatic and rigiddynamic
			 */
			virtual void					init_physics() = 0;
			virtual void					add_force(double);
			//virtual void					setPose(neb::fnd::pose const & pose) = 0;
			virtual void					createControlManual(std::shared_ptr<neb::fnd::input::source> window);
			void						createControlPD();
		public:
			control_shared					control_;
			glm::vec3					force_;
			glm::vec3					torque_;
	};
}}}}}

#endif


