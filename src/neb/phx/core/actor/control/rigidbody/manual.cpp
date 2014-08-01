

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <PxPhysicsAPI.h>

#include <Galaxy-Log/log.hpp>
#include <neb/debug.hh>

#include <neb/phx/core/actor/rigidbody/base.hpp>
#include <neb/phx/core/actor/control/rigidbody/base.hpp>
#include <neb/phx/util/convert.hpp>

void		neb::phx::core::actor::control::rigidbody::manual::step(gal::std::timestep const & ts) { // 0

}

vec3			neb::phx::core::actor::control::rigidbody::manual::f_body() {
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "phx core actor", debug) << __PRETTY_FUNCTION__;
	return f_ * 10.0f;
}
vec3			neb::phx::core::actor::control::rigidbody::manual::t_body() {
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "phx core actor", debug) << __PRETTY_FUNCTION__;
	return t_ * 3.0f;
}
vec3			neb::phx::core::actor::control::rigidbody::manual::f_global() {
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "phx core actor", debug) << __PRETTY_FUNCTION__;
	return vec3();
}
vec3			neb::phx::core::actor::control::rigidbody::manual::t_global() {
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "phx core actor", debug) << __PRETTY_FUNCTION__;
	return vec3();
}



