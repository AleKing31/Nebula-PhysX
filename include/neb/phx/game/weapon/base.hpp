#ifndef PHYSX_GAME_WEAPON_BASE_HPP
#define PHYSX_GAME_WEAPON_BASE_HPP

#include <gal/stl/child.hpp>

#include <neb/core/itf/shared.hpp>

#include <neb/phx/core/actor/util/decl.hpp>

namespace neb {

	namespace gfx { namespace window {
		class base;
	}}


	namespace phx { namespace game { namespace weapon {
		namespace util {
			class parent;
		}

		class base:
			virtual public neb::itf::shared,
			virtual public gal::stl::child<neb::phx::game::weapon::util::parent>
		{
			public:
				typedef neb::phx::game::weapon::util::parent parent_t;
				base();
				virtual void					init(parent_t * const & p);

				virtual void					step(gal::etc::timestep const &) {}
				virtual void					connect(std::shared_ptr<neb::gfx::window::base> window) = 0;
				virtual int					key_fun(std::shared_ptr<neb::gfx::window::base> window, int, int, int, int) = 0;
				virtual void					fire() = 0;

				/** @brief last
				 *
				 * last time weapon was fired
				 */
				double						last_;
				/** @brief cooldown
				 */
				double						cooldown_;

				std::weak_ptr<neb::phx::core::actor::base>	actor_;

		};

	}}}

}

#endif


