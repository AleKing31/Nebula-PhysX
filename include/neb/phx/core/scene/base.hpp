#ifndef PHYSX_CORE_SCENE_BASE_HPP
#define PHYSX_CORE_SCENE_BASE_HPP

#include <vector>

#include <PxPhysicsAPI.h>

#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>

#include <gal/etc/flag.hpp>
#include <gal/stl/map.hpp>

#include <neb/core/core/actor/util/parent.hpp>
#include <neb/core/core/scene/base.hpp>
#include <neb/core/math/serialization/glm.hpp>
#include <neb/core/util/decl.hpp>
#include <neb/core/net/util/decl.hpp>
#include <neb/core/DebugBuffer.hpp>

#include <neb/phx/tmp/Child.hpp>
#include <neb/phx/core/actor/util/decl.hpp>
#include <neb/phx/core/actor/util/parent.hpp>
#include <neb/phx/simulation_callback.hh>

typedef weak_ptr<neb::fnd::core::actor::base> wbase;

namespace neb { namespace phx { namespace core { namespace scene {
	/** 
	 * @ingroup group_core
	 * @brief base
	 */
	class base:
		virtual public neb::fnd::core::scene::base,
		virtual public neb::phx::tmp::Child<neb::fnd::core::scene::util::parent>
	{
		public:
			using CHILD::get_fnd_app;
			friend class neb::fnd::net::core::scene::Base;
			base();
			virtual ~base();
			void					__init(parent_t * const & p);
			void					init_light();
			virtual void				release();
			void					step(gal::etc::timestep const & ts);
			neb::fnd::DebugBuffer			get_debug_buffer();
		private:
			void					step_physics(gal::etc::timestep const & ts);
			void					create_physics();
		public:
			virtual void				load(boost::archive::polymorphic_iarchive & ar, unsigned int const & version);
			virtual void				save(boost::archive::polymorphic_oarchive & ar, unsigned int const & version) const;
			BOOST_SERIALIZATION_SPLIT_MEMBER();
			/** @name convenience functions
			 * @{
			 */
			/** @brief create rigiddynamic
			 *
			 * @note typeof returned actor will be determined by final implementation of this
			 *
			 * @warning return actor is not initialized
			 */
			virtual weak_ptr<neb::fnd::core::actor::base>		createActorRigidStaticUninitialized() = 0;
			/** @brief create rigidstatic
			 *
			 * @note typeof returned actor will be determined by final implementation of this
			 *
			 * @warning return actor is not initialized
			 */
			virtual weak_ptr<neb::fnd::core::actor::base>		createActorRigidDynamicUninitialized() = 0;
			/** @} */




		public:
			physx::PxScene*						px_scene_;
			physx::PxSimulationFilterShader				px_filter_shader_;
			neb::phx::simulation_callback*				simulation_callback_;
			
			glm::vec3						gravity_;
			//neb::vehicle_manager					vehicle_manager_;
	};
}}}}

#endif





