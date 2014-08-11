#ifndef PHYSX_CORE_ACTOR_BASE
#define PHYSX_CORE_ACTOR_BASE

#include <neb/core/actor/base.hpp>

#include <neb/phx/core/actor/util/cast.hpp>
#include <neb/phx/core/actor/util/decl.hpp>
#include <neb/phx/core/actor/util/parent.hpp>
#include <neb/phx/core/shape/util/parent.hpp>
#include <neb/phx/game/weapon/util/parent.hpp>
#include <neb/phx/game/weapon/util/decl.hpp>
#include <neb/phx/filter.hpp>

namespace neb { namespace phx { namespace core { namespace actor {

	class base:
		virtual public neb::core::actor::base,
		virtual public neb::phx::core::actor::util::parent,
		virtual public neb::phx::core::shape::util::parent,
		virtual public neb::phx::game::weapon::util::parent,
		virtual public neb::phx::core::actor::util::cast
	{
		public:
			base(sp::shared_ptr<neb::phx::core::actor::util::parent> parent);

			
			virtual void		init();
			virtual void		release() = 0;
			virtual void		step(gal::std::timestep const & ts);

			void			hit();
			void			damage(double);

			
			virtual void		create_physics() = 0;
			virtual void		init_physics() = 0;

			template<typename Archive> void		serializeTemplate(Archive & ar, unsigned int const & version) {
				ar & boost::serialization::make_nvp("filter_data_simulation",simulation_);
				ar & boost::serialization::make_nvp("filter_data_scene_query",scene_query_);

			}
	
			sp::shared_ptr<neb::phx::core::actor::util::parent>			getPxParent();

			/** @name convenience functions
			 * @{
			 */
			/** @brief create simple projectile weapon
			 */
			sp::weak_ptr<neb::phx::game::weapon::SimpleProjectile>			createWeaponSimpleProjectile(
					sp::shared_ptr<neb::gfx::window::base> window,
					double size,
					double damage,
					double velocity);
			/** @} */
		public:
			sp::weak_ptr<neb::phx::core::actor::util::parent>			parent_;

			phx::filter::data							simulation_;
			phx::filter::data							scene_query_;

			double									health_;

	};


}}}}

#endif
