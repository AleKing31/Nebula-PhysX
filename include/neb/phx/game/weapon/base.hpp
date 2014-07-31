#ifndef PHYSX_GAME_WEAPON_BASE_HPP
#define PHYSX_GAME_WEAPON_BASE_HPP

#include <neb/util/shared.hpp>

#include <PhysX/core/actor/util/decl.hpp>

namespace neb {

	namespace gfx { namespace window {
		class base;
	}}


	namespace phx { namespace game { namespace weapon {

		class base: virtual public neb::std::shared {
			public:
				base();

				virtual void					connect(sp::shared_ptr<neb::gfx::window::base> window) = 0;
				virtual int					key_fun(sp::shared_ptr<neb::gfx::window::base> window, int, int, int, int) = 0;
				virtual void					fire() = 0;

				/** @brief last
				 *
				 * last time weapon was fired
				 */
				double						last_;
				/** @brief cooldown
				 */
				double						cooldown_;

				sp::weak_ptr<neb::phx::core::actor::base>	actor_;

		};

	}}}

}

#endif


