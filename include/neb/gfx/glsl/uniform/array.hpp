#ifndef NEB_GFX_GLSL_UNIFORM_ARRAY_HPP
#define NEB_GFX_GLSL_UNIFORM_ARRAY_HPP

#include <stdio.h>
#include <tuple>
#include <memory>
#include <iostream>
#include <iomanip>
#include <map>

#include <gal/stl/helper.hpp>

#include <neb/gfx/util/io.hpp>
#include <neb/gfx/opengl/uniform.hpp>
#include <neb/gfx/glsl/util/decl.hpp>
#include <neb/gfx/util/array.hpp>
#include <neb/gfx/util/log.hpp>

#include <neb/gfx/glsl/program/base.hpp>

namespace neb { namespace gfx { namespace glsl { namespace uniform {
	template<int I, typename D> class locations;

	/** @brief array
	 * abstract class for managing sequential data arrays.
	 * So data for arrays of uniforms can be loaded faster.
	 *
	 * For example, an array is used for light positions.
	 * The core light object is stored elsewhere and registers for a slot in the array.
	 *
	 * Used by:
	 * lights
	 *
	 */
	typedef neb::gfx::glsl::program::base		P;

	template<typename LOC_DER, class... T> class array: public neb::gfx::array<T...> {
		public:
			typedef locations<sizeof...(T), LOC_DER>		loc_type;
			typedef typename gens<sizeof...(T)>::type		seq_type;
			typedef std::map<P*, loc_type>				loc_map;
		public:
			virtual int				reg(T... initial) {
				int i = neb::gfx::array<T...>::reg_array(initial...);

				markLoadAll();				

				return i;
			}
			void					markLoadAll()
			{
				for(typename loc_map::value_type& p: _M_locations)
				{
					p.second.markLoadAll();
				}
			}
			void					markLoadClosed()
			{
				for(typename loc_map::value_type& p: _M_locations)
				{
					p.second.load_closed = 1;
					p.second.load_any = 1;
				}
			}
			void					markLoad(int i)
			{
				for(typename loc_map::value_type& p: _M_locations)
				{
					p.second.load[i] = 1;
					p.second.load_any = 1;
				}
			}
			void					unreg(int i) {
				neb::gfx::array<T...>::unreg_array(i);

				markLoadClosed();
			}
			template<int I, typename U> void	set(int i, U const & u) {
				neb::gfx::array<T...>::template set_array<I>(i, u);

				markLoad(I);
			}
			void					load_uniform(P* p)
			{
				loc_type& loc = _M_locations[p];
				loc.check(p);
				load_uniform(loc);
			}
		private:
			void					load_uniform(loc_type& loc) {
				if(loc.load_any == 1) {
					load_uniform(seq_type(), loc);

					if(loc.load_closed == 1) {

						neb::gfx::ogl::glUniformv(
								loc.location[sizeof...(T)],
								neb::gfx::array<T...>::size,
								neb::gfx::array<T...>::closed);

						loc.load_closed = 0;
					}

					neb::gfx::ogl::glUniform(
							loc.location[sizeof...(T)+1],
							(int)neb::gfx::array<T...>::size);

					LOG(lg, neb::gfx::sl, debug) << "load_uniform size=" << neb::gfx::array<T...>::size;

					loc.load_any = 0;
				}
			}
			template<int... S> void			load_uniform(seq<S...>, loc_type& loc) {
				//pass((std::cout << S << std::endl)...);
				pass(load_uniform__<S,T>(loc)...);
			}
			template<int I, typename U> int		load_uniform__(loc_type& loc) {

				if(loc.load[I] == 1)
				{
					LOG(lg, neb::gfx::sl, debug) << "load_uniform__ I=" << I << " loc=" << loc.location[I];
					for(int i = 0; i < neb::gfx::array<T...>::size; i++) {

						//std::get<I>(neb::gfx::array_basic<T...>::data_)[i]
						//neb::gfx::array_basic<T...>::get<I,U>(i)

						LOG(lg, neb::gfx::sl, debug) << std::setw(32) << neb::gfx::array_basic<T...>::template get<I,U>(i);
					}

					neb::gfx::ogl::glUniformv(
							loc.location[I],
							neb::gfx::array<T...>::size,
							neb::gfx::array_basic<T...>::template get<I,U>());

					loc.load[I] = 0;
				}
				return 0;
			}
			loc_map		_M_locations;
	};
	template<int I, typename D> class locations {
		public:
			enum {
				N = I + 2
			};

			locations()
			{
				markLoadAll();
			}
			void					markLoadAll()
			{
				for(int j = 0; j < N; j++) {
					load[j] = 1;
				}
				load_closed = 1;
				load_any = 1;

			}
			void					check(P* p)
			{
				for(unsigned int i = 0; i < N; i++)
				{
					location[i] = p->uniform_table_[D::names_[i]];
					std::cout << "location[" << i << "] = " << location[i] << std::endl;
				}
			}
			GLint					location[I+2];
			int					load[I+2];
			int					load_any;
			int					load_closed;
	};
}}}}



#endif

