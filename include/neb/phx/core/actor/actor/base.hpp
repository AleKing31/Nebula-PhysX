#ifndef __PX_CONTENT_ACTOR_PHYSICS_ACTOR_HPP__
#define __PX_CONTENT_ACTOR_PHYSICS_ACTOR_HPP__

#include <PxPhysicsAPI.h>

#include <gal/math/pose.hpp>

#include <neb/phx/core/actor/base.hpp>
#include <neb/phx/core/actor/util/decl.hpp>

namespace neb { namespace phx { namespace core { namespace actor { namespace actor {
	class base:
		virtual public neb::phx::core::actor::base
	{

		public:
			base();
			//base(std::shared_ptr<>);
			virtual ~base();
			//virtual void					init(neb::phx::core::actor::util::parent * const &) = 0;
			virtual void					release();
		protected:
			//void							releaseUp();
		public:	
			virtual void					step(gal::etc::timestep const & ts) = 0;
			virtual void					create_physics() = 0;
			virtual void					init_physics() = 0;
			//virtual void					add_force(real) = 0;
			//virtual void					setPose(neb::fnd::pose const & pose) = 0;
		public:
			physx::PxActor*					px_actor_;
	};



}}}}}


#endif


