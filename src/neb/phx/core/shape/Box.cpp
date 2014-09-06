
#include <neb/phx/util/convert.hpp>
#include <neb/phx/core/shape/box.hpp>
#include <neb/phx/core/actor/rigidactor/base.hpp>

neb::phx::core::shape::box::box()
{
}
physx::PxGeometry*		neb::phx::core::shape::box::to_geo() {
	return new physx::PxBoxGeometry(
			scale_[0] * 0.5f,
			scale_[1] * 0.5f,
			scale_[2] * 0.5f
			);
}



