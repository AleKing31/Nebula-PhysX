#include <neb/fnd/util/cast.hpp>
#include <neb/fnd/util/debug.hpp>
#include <neb/fnd/core/shape/base.hpp>
#include <neb/fnd/core/light/base.hpp>

//#include <neb/gfx/glsl/attrib.hh>

#include <neb/phx/app/base.hpp>
#include <neb/phx/core/shape/base.hpp>
#include <neb/phx/core/actor/rigidactor/base.hpp>


neb::phx::core::shape::base::base():
	px_shape_(NULL)
{
}
neb::phx::core::shape::base::~base()
{
	printv_func(DEBUG);
	assert(px_shape_ == NULL);
}
void			neb::phx::core::shape::base::step(gal::etc::timestep const & ts) {
	printv_func(DEBUG);
}
void			neb::phx::core::shape::base::init(neb::fnd::core::shape::util::parent * const & p)
{
	printv_func(DEBUG);
}
void			neb::phx::core::shape::base::release() {
	//NEBULA_DEBUG_0_FUNCTION;
	printv_func(DEBUG);

	neb::fnd::core::shape::base::release();
	
	if(px_shape_) {
		auto p = getParent();
		assert(p);
		auto ra = dynamic_cast<neb::phx::core::actor::rigidactor::base*>(p);
		assert(ra);		

		assert(ra->px_actor_);
		auto pxra = ra->px_actor_->isRigidActor();
		assert(pxra);
		
		pxra->detachShape(*px_shape_);
		
		//px_shape_->release();
		px_shape_ = NULL;
	}
}
void			neb::phx::core::shape::base::create_physics()
{
	printv_func(DEBUG);
	//NEBULA_DEBUG_0_FUNCTION;

	if(!hasParent()) return;

	auto actor = neb::could_be<parent_t, neb::phx::core::actor::base>(getParent());

	if(!actor) return;

	auto rigidactor = actor->isPxActorRigidActorBase();//std::dynamic_pointer_cast<neb::fnd::actor::Rigid_Actor>(parent_.lock());

	if(!rigidactor) return;

	physx::PxActor* const & px_actor = rigidactor->px_actor_;

	if(!px_actor) return;

	auto px_rigidactor = rigidactor->px_actor_->isRigidActor();
	assert(px_rigidactor);

	physx::PxMaterial* px_mat = get_phx_app()->px_physics_->createMaterial(1,1,1);

	px_shape_ = px_rigidactor->createShape( *(to_geo()), *px_mat );
}
/*shared_ptr<neb::phx::core::shape::util::parent>		neb::phx::core::shape::base::getPxParent() {

  auto parent = getParent();

  auto pxparent(dynamic_cast<neb::phx::core::shape::util::parent*>(parent));

  if(!pxparent) {
  abort();
  }

  return pxparent;
  }*/
physx::PxGeometry*	neb::phx::core::shape::base::to_geo()
{
	printv_func(DEBUG);
	return 0;
}







