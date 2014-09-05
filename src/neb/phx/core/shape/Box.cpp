
#include <neb/phx/util/convert.hpp>
#include <neb/phx/core/shape/box.hpp>
#include <neb/phx/core/actor/rigidactor/base.hpp>

neb::phx::core::shape::box::box()
{
}
physx::PxGeometry*		neb::phx::core::shape::box::to_geo() {
	return new physx::PxBoxGeometry(neb::phx::util::convert(scale_ * 0.5f));
}



