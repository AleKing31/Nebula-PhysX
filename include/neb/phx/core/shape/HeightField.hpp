#ifndef PHYSX_SHAPE_HEIGHT_FIELD_HH
#define PHYSX_SHAPE_HEIGHT_FIELD_HH

#include <neb/core/math/geo/util/decl.hpp>

#include <neb/core/core/shape/HeightField.hpp>

#include <neb/phx/core/shape/base.hpp>

namespace neb { namespace phx { namespace core { namespace shape {

	class HeightField:
		virtual public neb::phx::core::shape::base
	{
		public:
			typedef neb::core::core::shape::util::parent parent_t;

			HeightField();
			
			virtual void				init(parent_t * const & p);
			virtual void				release();
			virtual void				step(gal::etc::timestep  const & ts);

			virtual void				create_physics();

			virtual void				load(ba::polymorphic_iarchive & ar, unsigned int const &);
			virtual void				save(ba::polymorphic_oarchive & ar, unsigned int const &) const;

			virtual physx::PxGeometry*		to_geo();

			void					mesh_from_heightfield(nc::math::geo::HeightField::Base*, float, float);

	};



}}}}

#endif
