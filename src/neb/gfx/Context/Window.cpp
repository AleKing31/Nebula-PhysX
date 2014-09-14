#include <neb/gfx/Context/Window.hpp>
#include <neb/gfx/window/Base.hh>

neb::gfx::context::window::window()
{
}
void		neb::gfx::context::window::init(parent_t * const & p)
{
	neb::gfx::context::base::__init();

	auto window = parent_.lock()->isWindowBase();

	resize(window->w_, window->h_);
}


