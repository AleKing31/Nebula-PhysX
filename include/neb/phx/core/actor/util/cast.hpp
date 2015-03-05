#ifndef PHYSX_CORE_ACTOR_UTIL_CAST_HPP
#define PHYSX_CORE_ACTOR_UTIL_CAST_HPP

#include <neb/phx/core/actor/util/decl.hpp>

namespace neb { namespace phx { namespace core { namespace actor { namespace util {
	class cast:
		virtual public gal::itf::shared
	{
		public:
			std::shared_ptr<neb::phx::core::actor::base>				isPxActorBase();
			std::shared_ptr<neb::phx::core::actor::actor::base>			isPxActorActorBase();
			std::shared_ptr<neb::phx::core::actor::rigidactor::base>			isPxActorRigidActorBase();
			std::shared_ptr<neb::phx::core::actor::rigidbody::base>			isPxActorRigidBodyBase();
			std::shared_ptr<neb::phx::core::actor::rigiddynamic::base>		isPxActorRigidDynamicBase();
			std::shared_ptr<neb::phx::core::actor::rigidstatic::base>		isPxActorRigidStaticBase();

	};
}}}}}

#endif



