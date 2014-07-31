#ifndef PHYSX_GAME_WEAPON_SIMPLE_PROJECTILE_HPP
#define PHYSX_GAME_WEAPON_SIMPLE_PROJECTILE_HPP

#include <neb/phx/game/weapon/base.hpp>

namespace neb { namespace phx { namespace game { namespace weapon {

	class SimpleProjectile: virtual public neb::phx::game::weapon::base {
		public:

			SimpleProjectile();
			
			virtual void					connect(sp::shared_ptr<neb::gfx::window::base> window);
			virtual int					key_fun(sp::shared_ptr<neb::gfx::window::base> window, int, int, int, int);
			virtual void					fire();
		
			real						size_;
			real						velocity_;
			real						damage_;

			sp::weak_ptr<phx::core::actor::base>		actor_;

	};

}}}}

#endif
