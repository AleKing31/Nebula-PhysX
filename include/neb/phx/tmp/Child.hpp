#ifndef NEB_PHX_TMP_CHILD_HPP
#define NEB_PHX_TMP_CHILD_HPP

#include <neb/core/tmp/Child.hpp>

namespace neb { namespace phx { namespace app { namespace util {
	template<class T> class Child:
		virtual public neb::fnd::tmp::Child<T>
	{
		neb::phx::app::base*	get_phx_app();
	}
}}}}

#endif
