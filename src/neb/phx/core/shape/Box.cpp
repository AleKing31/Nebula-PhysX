
#include <neb/fnd/core/shape/base.hpp>

#include <neb/phx/core/shape/box.hpp>
//#include <neb/phx/core/actor/rigidactor/base.hpp>

typedef neb::phx::core::shape::box THIS;

THIS::box()
{
}
void				THIS::init(parent_t * const & p)
{
	printf("%s\n", __PRETTY_FUNCTION__);
	printv_func(DEBUG);

	setParent(p);

	create_physics();
}
void				THIS::release()
{
	neb::phx::core::shape::base::release();
}
void				THIS::step(gal::etc::timestep const & ts)
{
}
physx::PxGeometry*		THIS::to_geo()
{
	printf("%s\n", __PRETTY_FUNCTION__);

	auto p = getParent();
	
	return new physx::PxBoxGeometry(
			p->scale_[0] * 0.5f,
			p->scale_[1] * 0.5f,
			p->scale_[2] * 0.5f
			);
}



