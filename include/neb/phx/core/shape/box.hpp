#ifndef PHYSX_SHAPE_BOX_HH
#define PHYSX_SHAPE_BOX_HH


#include <neb/phx/core/shape/base.hpp>

namespace neb { namespace phx { namespace core { namespace shape {


	class box:
		virtual public neb::phx::core::shape::base
	{
		public:
			box(sp::shared_ptr<phx::core::actor::rigidactor::base> parent);

			virtual void				init() = 0;
			virtual void				release() = 0;
			virtual void				step(gal::std::timestep  const & ts) = 0;


			virtual physx::PxGeometry*		to_geo();
	};



}}}}

#endif
