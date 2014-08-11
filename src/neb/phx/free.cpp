
#include <neb/core/free.hpp>

#include <neb/phx/app/base.hpp>
#include <neb/phx/free.hpp>

void	neb::phx::init() {
	
	neb::init_log();
	
	auto app(sp::make_shared<neb::phx::app::base>());
	
	neb::core::app::__base::g_app_ = app;

	app->init();

}


