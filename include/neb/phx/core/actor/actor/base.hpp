#ifndef __PX_CONTENT_ACTOR_PHYSICS_ACTOR_HPP__
#define __PX_CONTENT_ACTOR_PHYSICS_ACTOR_HPP__

#include <PxPhysicsAPI.h>

#include <neb/core/pose.hpp>

#include <neb/phx/core/actor/base.hpp>
#include <neb/phx/core/actor/util/decl.hpp>

namespace neb { namespace phx { namespace core { namespace actor { namespace actor {
	class base:
		virtual public neb::phx::core::actor::base
	{

		public:
			base(sp::shared_ptr<neb::phx::core::actor::util::parent>);
			virtual ~base();
			virtual void					init() = 0;
			virtual void					release() = 0;
		protected:
			//void							releaseUp();
		public:	
			virtual void					step(gal::std::timestep const & ts) = 0;
			virtual void					create_physics() = 0;
			virtual void					init_physics() = 0;
			//virtual void					add_force(real) = 0;
			//virtual void					setPose(neb::core::pose const & pose) = 0;
		public:
			physx::PxActor*					px_actor_;
	};



}}}}}


#endif


