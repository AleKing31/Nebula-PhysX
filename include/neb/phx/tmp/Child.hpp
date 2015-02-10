#ifndef NEB_PHX_TMP_CHILD_HPP
#define NEB_PHX_TMP_CHILD_HPP

#include <neb/core/tmp/Child.hpp>

#include <neb/phx/app/util/decl.hpp>

namespace neb { namespace phx { namespace tmp {
	template<class T> class Child:
		virtual public neb::fnd::tmp::Child<T>
	{
		public:
		neb::phx::app::base*	get_phx_app();
	};
}}}

#endif
