#ifndef PHYSX_CORE_ACTOR_PARENT_HPP
#define PHYSX_CORE_ACTOR_PARENT_HPP

#include <neb/core/actor/util/parent.hpp>


namespace neb { namespace phx { namespace core {

	namespace scene {
		class base;
	}

	namespace actor { namespace util {



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
				sp::shared_ptr<neb::phx::core::scene::base>			getScene();
		};



	}}}
}}

#endif



