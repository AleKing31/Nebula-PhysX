#ifndef PHYSX_SHAPE_HEIGHT_FIELD_HH
#define PHYSX_SHAPE_HEIGHT_FIELD_HH


#include <neb/gfx/core/shape/base.hpp>
#include <neb/phx/core/shape/base.hpp>

namespace neb { namespace phx { namespace core { namespace shape {


	class HeightField:
		virtual public neb::phx::core::shape::base,
		virtual public neb::gfx::core::shape::base
	{
		public:
			HeightField(std::shared_ptr<neb::core::core::shape::util::parent>);

			virtual void				init();
			virtual void				release();
			virtual void				step(gal::etc::timestep  const & ts);
			virtual void				create_physics();
			void					__init();


			virtual physx::PxGeometry*		to_geo();


	};



}}}}

#endif
