#ifndef PHYSX_SHAPE_BASE_H__
#define PHYSX_SHAPE_BASE_H__

#include <map>

#include <PxPhysicsAPI.h>

#include <neb/fnd/core/shape/base.hpp>

#include <neb/phx/core/shape/util/parent.hpp>
#include <neb/phx/tmp/Child.hpp>

namespace neb { namespace phx { namespace core { namespace shape {
	class base:
		virtual public neb::fnd::core::shape::base,
		virtual public neb::phx::tmp::Child<neb::fnd::core::shape::util::parent>
	{
		public:
			base();
			virtual ~base();
			virtual void		init(neb::fnd::core::shape::util::parent * const & p);
			virtual void		release();
			virtual void		step(gal::etc::timestep const & ts);
			virtual void		create_physics();
			virtual physx::PxGeometry*	to_geo();
		public:
			//std::shared_ptr<phx::core::shape::util::parent>		getPxParent();

			physx::PxShape*		px_shape_;


	};

}}}}

#endif




