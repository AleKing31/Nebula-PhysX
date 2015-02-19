

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <PxPhysicsAPI.h>

#include <gal/log/log.hpp>

#include <neb/core/util/debug.hpp>

#include <neb/phx/core/actor/rigidbody/base.hpp>
#include <neb/phx/core/actor/control/rigidbody/base.hpp>
#include <neb/phx/util/convert.hpp>
#include <neb/phx/util/log.hpp>

typedef neb::phx::core::actor::control::rigidbody::manual THIS;

THIS::~manual()
{
}
void			THIS::step(gal::etc::timestep const & ts)
{
}
glm::vec3		THIS::f_body()
{
	LOG(lg, neb::phx::core::actor::sl, debug) << __PRETTY_FUNCTION__;
	return f_ * 10.0f;
}
glm::vec3		THIS::t_body()
{
	LOG(lg, neb::phx::core::actor::sl, debug) << __PRETTY_FUNCTION__;
	return t_ * 3.0f;
}
glm::vec3		THIS::f_global()
{
	LOG(lg, neb::phx::core::actor::sl, debug) << __PRETTY_FUNCTION__;
	return glm::vec3();
}
glm::vec3		THIS::t_global()
{
	LOG(lg, neb::phx::core::actor::sl, debug) << __PRETTY_FUNCTION__;
	return glm::vec3();
}



