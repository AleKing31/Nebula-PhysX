#ifndef PHYSX_CORE_SCENE_BASE_HPP
#define PHYSX_CORE_SCENE_BASE_HPP

#include <vector>

#include <PxPhysicsAPI.h>

#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>

#include <gal/std/flag.hpp>
#include <gal/std/map.hpp>

#include <neb/core/util/decl.hpp>
#include <neb/core/util/typedef.hpp>
#include <neb/core/math/Serialization/glm.hpp>
#include <neb/core/actor/util/parent.hpp>
#include <neb/core/scene/base.hpp>

#include <neb/phx/core/actor/util/decl.hpp>
#include <neb/phx/core/actor/util/parent.hpp>
#include <neb/phx/simulation_callback.hh>

namespace neb {
	namespace phx {
		//class simulation_callback;
		namespace core {
			namespace scene {
				/** 
				 * @ingroup group_core
				 * @brief base
				 */
				class base:
					virtual public neb::core::core::scene::base,
					virtual public phx::core::actor::util::parent
				{
					public:
						base(shared_ptr<neb::core::core::scene::util::parent> parent);
						virtual ~base();
						void					init();
						void					release();
						void					step(::gal::std::timestep const & ts);
					public:
						void					create_physics();
						virtual  void				serialize(
								boost::archive::polymorphic_iarchive & ar, unsigned int const & version) {
							ar & boost::serialization::make_nvp("gravity",gravity_);
						}
						virtual void				serialize(
								boost::archive::polymorphic_oarchive & ar, unsigned int const & version) {
							ar & boost::serialization::make_nvp("gravity",gravity_);
						}

						/** @name convenience functions
						 * @{
						 */
						/** @brief create rigidstatic
						 *
						 * @note typeof returned actor will be determined by final implementation of this
						 *
						 * @warning return actor is not initialized
						 */
						virtual weak_ptr<neb::core::actor::base>		createActorRigidStaticUninitialized() = 0;
						/** @} */
					public:
						physx::PxScene*						px_scene_;
						physx::PxSimulationFilterShader				px_filter_shader_;
						neb::phx::simulation_callback*				simulation_callback_;
						vec3							gravity_;
						//neb::vehicle_manager					vehicle_manager_;
				};
			}
		}
	}
}

#endif





