#include <neb/gfx/util/log.hpp>
#include <neb/gfx/glsl/program/simple3.hpp>

void		neb::gfx::glsl::program::simple3::init() {
	
	neb::gfx::glsl::program::base::init();

	add_shader("v130/simple3/vs.glsl", GL_VERTEX_SHADER);
	add_shader("v130/simple3/fs.glsl", GL_FRAGMENT_SHADER);

	compile();

	scanUniforms();
	locate();


}

