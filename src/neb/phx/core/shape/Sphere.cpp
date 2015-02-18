
#include <neb/phx/core/shape/sphere.hpp>

typedef neb::phx::core::shape::sphere THIS;

physx::PxGeometry*		THIS::to_geo()
{
	return new physx::PxSphereGeometry(scale_.x);
}



