#ifndef PHYSX_CORE_ACTOR_PARENT_HPP
#define PHYSX_CORE_ACTOR_PARENT_HPP

#include <neb/core/actor/util/Parent.hh>

#include <PhysX/core/scene/util/decl.hpp>

namespace phx { namespace core { namespace actor { namespace util {



	/** @brief @parent
	 * abstract class for parent of a %phx %actor
	 */
	class parent:
		virtual public neb::core::actor::util::parent
	{
		public:
			parent();
			virtual ~parent();

			virtual void						init();
		public:
			sp::shared_ptr<phx::core::scene::base>			getScene();
	};



}}}}

#endif



