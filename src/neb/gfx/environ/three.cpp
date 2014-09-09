#include <gal/log/log.hpp>


#include <neb/core/util/debug.hpp>
#include <neb/core/util/cast.hpp>

#include <neb/gfx/app/__gfx_glsl.hpp>

#include <neb/gfx/camera/view/Free.hh>
#include <neb/gfx/camera/view/ridealong.hh>
#include <neb/gfx/camera/proj/perspective.hpp>

#include <neb/gfx/environ/three.hpp>
#include <neb/gfx/drawable/base.hpp>
#include <neb/gfx/util/log.hpp>
#include <neb/gfx/glsl/program/threed.hpp>

#include <neb/phx/core/scene/base.hpp>

void		neb::gfx::environ::three::init() {
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;

	auto self = std::dynamic_pointer_cast<neb::gfx::environ::three>(shared_from_this());


	//programs_.reset(new neb::gfx::glsl::program::threed("3d"));
	//programs_->init();


	// camera
//	if(!view_) {
//		view_.reset(new neb::gfx::camera::view::Free(self));
//	}

	proj_.reset(new neb::gfx::camera::proj::perspective(self));
	//camera_->init(shared_from_this());



}
void		neb::gfx::environ::three::step(gal::etc::timestep const & ts) {

	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;

	//if(proj_) proj_->step(ts);	
	//if(view_) view_->step(ts);	

}
/*
void		neb::gfx::environ::three::render(std::shared_ptr<neb::gfx::context::base> context) {

	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;

	// prepare rendering environment and then call the drawable

	
	auto drawable = drawable_.lock();

	if(!drawable) {
		LOG(lg, neb::gfx::sl, warning) << "drawable is NULL";
		return;
	}

	//auto self = std::dynamic_pointer_cast<neb::gfx::context::base>(shared_from_this());
	//auto app = neb::gfx::app::__gfx_glsl::global().lock();

	// wrong for color maybe! 	
	//glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	//glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	//assert(proj_);
	//assert(view_);
	
	//program_->use();
	
	viewport_.load();
	
	//proj_->load(program_);
	//view_->load(program_);
	
	drawable->draw(
			RenderDesc(
				view_,
				proj_,
				programs_.d3_,
				programs_.d3_inst_
				)
		      );

	auto scene = neb::could_be<neb::gfx::drawable::base, neb::phx::core::scene::base>(drawable);

	if(scene) scene->drawPhysxVisualization(context);
	
}		
*/




