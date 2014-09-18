#ifndef NEB_GFX_GLSL_BUFFER_MESH_HPP
#define NEB_GFX_GLSL_BUFFER_MESH_HPP

#include <memory>

#include <GL/glew.h>

#include <neb/core/math/geo/vertex.hpp>

#include <neb/gfx/glsl/util/decl.hpp>
#include <neb/gfx/glsl/buffer/base.hpp>

namespace neb { namespace gfx { namespace glsl { namespace buffer {
	class tri1: 
		public neb::gfx::glsl::buffer::base<
		tri1,
		array_type::VEC3,
		array_type::VEC3,
		array_type::VEC2,
		array_type::VEC3,
		array_type::VEC3 >
	{
		public:
			typedef std::shared_ptr<neb::gfx::glsl::program::base> program_shared;
			//const math::geo::vertex v;

			typedef GLushort index_type;

			static constexpr GLenum			target_[BUFFER_COUNT] = {
				GL_ARRAY_BUFFER,
				GL_ELEMENT_ARRAY_BUFFER
			};
			static constexpr GLenum			usage_[BUFFER_COUNT] = {
				GL_STATIC_DRAW,
				GL_STATIC_DRAW
			};
			static constexpr GLsizeiptr		datasize_[BUFFER_COUNT] = {
				sizeof(math::geo::vertex),
				sizeof(index_type)
			};
/*			static constexpr GLint			size_array_[ATTRIB_COUNT] = {
				3,3,2,3,3
			};
*/
/*			static constexpr GLenum			type_[ATTRIB_COUNT] = {
				GL_FLOAT,
				GL_FLOAT,
				GL_FLOAT,
				GL_FLOAT,
				GL_FLOAT
			};
			static constexpr GLboolean		normalized_[ATTRIB_COUNT] = {
				GL_FALSE,
				GL_FALSE,
				GL_FALSE,
				GL_FALSE,
				GL_FALSE
			};
						static constexpr GLvoid* pointer[ATTRIB_COUNT] = {
						(GLvoid*)((long)&v.p[0]		- (long)&v),
						(GLvoid*)((long)&v.n[0]		- (long)&v),
						(GLvoid*)((long)&v.tc[0]	- (long)&v),
						(GLvoid*)((long)&v.tangent[0]	- (long)&v),
						(GLvoid*)((long)&v.binormal[0]	- (long)&v)
						};
			static constexpr GLvoid*		pointer_[ATTRIB_COUNT] = {
				(GLvoid*)0,
				(GLvoid*)12,
				(GLvoid*)24,
				(GLvoid*)32,
				(GLvoid*)44
			};*/

			static constexpr GLsizei		stride_[ATTRIB_COUNT] = {
				sizeof(math::geo::vertex),
				sizeof(math::geo::vertex),
				sizeof(math::geo::vertex),
				sizeof(math::geo::vertex),
				sizeof(math::geo::vertex)
			};
			static constexpr unsigned int		buffer_index_[ATTRIB_COUNT] = {
				0,0,0,0,0
			};
			static constexpr GLuint			divisor_[ATTRIB_COUNT] = {
				0,0,0,0,0
			};
			static constexpr neb::gfx::glsl::attribs::e	attribute_[ATTRIB_COUNT] = {
				neb::gfx::glsl::attribs::POSITION,
				neb::gfx::glsl::attribs::NORMAL,
				neb::gfx::glsl::attribs::TEXCOOR,
				neb::gfx::glsl::attribs::TANGENT,
				neb::gfx::glsl::attribs::BINORMAL
			};


			/*			virtual void				init(
						program_shared p);*/

	};
}}}}

#endif

