#ifndef NEB_GFX_GLSL_PROGRAM_SIMPLE3_HPP
#define NEB_GFX_GLSL_PROGRAM_SIMPLE3_HPP

#include <neb/gfx/glsl/uniform/array.hpp>
#include <neb/gfx/glsl/program/base.hpp>

namespace neb { namespace gfx { namespace glsl { namespace program {

	class simple3: public neb::gfx::glsl::program::base {
		public:
			simple3(): neb::gfx::glsl::program::base() {}
			virtual ~simple3() {}

			virtual void						init();

	};
}}}}

#endif

