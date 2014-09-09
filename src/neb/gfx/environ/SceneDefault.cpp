#include <neb/gfx/environ/SceneDefault.hpp>

std::weak_ptr<neb::gfx::camera::view::ridealong>		neb::gfx::environ::SceneDefault::createViewridealong(
		weak_ptr<neb::core::core::actor::base> actor)
{
	auto self(dynamic_pointer_cast<neb::gfx::environ::three>(shared_from_this()));

	auto view = make_shared<neb::gfx::camera::view::ridealong>(self, actor);
	view_ = view;
	return view;
}


