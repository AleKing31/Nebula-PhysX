

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <PxPhysicsAPI.h>

#include <gal/log/log.hpp>

#include <neb/fnd/util/debug.hpp>

#include <neb/phx/core/actor/rigidbody/base.hpp>
#include <neb/phx/core/actor/control/rigidbody/base.hpp>
#include <neb/phx/util/convert.hpp>

typedef neb::phx::core::actor::control::rigidbody::manual THIS;

THIS::~manual()
{
}
void			THIS::step(gal::etc::timestep const & ts)
{
}
glm::vec3		THIS::f_body()
{
	printv_func(DEBUG);
	return f_ * 10.0f;
}
glm::vec3		THIS::t_body()
{
	printv_func(DEBUG);
	return t_ * 3.0f;
}
glm::vec3		THIS::f_global()
{
	printv_func(DEBUG);
	return glm::vec3();
}
glm::vec3		THIS::t_global()
{
	printv_func(DEBUG);
	return glm::vec3();
}



