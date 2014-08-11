#include <gal/log/log.hpp>

#include <neb/core/scene/base.hpp>

#include <neb/core/debug.hh>
#include <neb/core/util/typedef.hpp>
#include <neb/core/shape/base.hpp>

#include <neb/phx/core/actor/util/parent.hpp>
#include <neb/phx/core/actor/actor/base.hpp>
#include <neb/phx/core/scene/base.hpp>

//neb::core::actor::actor::base::base() {
//}
neb::phx::core::actor::actor::base::base(sp::shared_ptr<neb::phx::core::actor::util::parent> parent):
	neb::core::actor::base(parent),
	neb::phx::core::actor::base(parent),
	px_actor_(NULL)
{
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "phx core actor", debug) << __PRETTY_FUNCTION__;
}
neb::phx::core::actor::actor::base::~base() {
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "phx core actor", debug) << __PRETTY_FUNCTION__;

	assert(px_actor_ == NULL);
}
void		neb::phx::core::actor::actor::base::release() {
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "phx core actor", debug) << __PRETTY_FUNCTION__;

	//neb::core::actor::base::releaseUp();

	if(px_actor_ != NULL) {	
		px_actor_->release();
		px_actor_ = NULL;
	}
	
	//assert(!scene_.expired());

}

