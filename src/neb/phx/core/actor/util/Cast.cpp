
#include <neb/phx/core/actor/rigiddynamic/base.hpp>
#include <neb/phx/core/actor/rigidstatic/base.hpp>
#include <neb/phx/core/actor/util/cast.hpp>

sp::shared_ptr<neb::phx::core::actor::base>				neb::phx::core::actor::util::cast::isPxActorBase() {
	return sp::dynamic_pointer_cast<neb::phx::core::actor::base>(shared_from_this());
}
sp::shared_ptr<neb::phx::core::actor::actor::base>			neb::phx::core::actor::util::cast::isPxActorActorBase() {
	return sp::dynamic_pointer_cast<neb::phx::core::actor::actor::base>(shared_from_this());
}
sp::shared_ptr<neb::phx::core::actor::rigidactor::base>			neb::phx::core::actor::util::cast::isPxActorRigidActorBase() {
	return sp::dynamic_pointer_cast<neb::phx::core::actor::rigidactor::base>(shared_from_this());
}
sp::shared_ptr<neb::phx::core::actor::rigidbody::base>			neb::phx::core::actor::util::cast::isPxActorRigidBodyBase() {
	return sp::dynamic_pointer_cast<neb::phx::core::actor::rigidbody::base>(shared_from_this());
}
sp::shared_ptr<neb::phx::core::actor::rigiddynamic::base>		neb::phx::core::actor::util::cast::isPxActorRigidDynamicBase() {
	return sp::dynamic_pointer_cast<neb::phx::core::actor::rigiddynamic::base>(shared_from_this());
}
sp::shared_ptr<neb::phx::core::actor::rigidstatic::base>		neb::phx::core::actor::util::cast::isPxActorRigidStaticBase() {
	return sp::dynamic_pointer_cast<neb::phx::core::actor::rigidstatic::base>(shared_from_this());
}


