#ifndef NEB_GFX_CORE_BUFFER_BASE_HPP
#define NEB_GFX_CORE_BUFFER_BASE_HPP

#include <iomanip>
#include <map>

#include <glm/gtx/transform.hpp>

#include <GL/glew.h>

#include <neb/core/pose.hpp>

#include <neb/gfx/free.hpp>
#include <neb/gfx/util/log.hpp>
#include <neb/gfx/opengl/vertex.hpp>
#include <neb/gfx/opengl/uniform.hpp>
#include <neb/gfx/glsl/buffer/traits.hpp>
#include <neb/gfx/glsl/program/base.hpp>

namespace neb { namespace gfx { namespace mesh {
	template<typename BUFFER> class base {
		protected:
			typedef std::map<neb::gfx::glsl::program::base const *, BUFFER*>	program_buffer_map;

			enum {
				BUFFER_COUNT = neb::gfx::glsl::buffer::traits<BUFFER>::BUFFER_COUNT,
				ATTRIB_COUNT = neb::gfx::glsl::buffer::traits<BUFFER>::ATTRIB_COUNT
			};

			virtual GLsizeiptr*		begin() = 0;
			virtual GLsizeiptr*		end() = 0;
			virtual GLsizeiptr*		size() = 0;
			virtual GLsizeiptr*		size_array() = 0;
			virtual GLvoid** const		data() = 0;

			/** set by function of same name then sent to bufferData functions */
			GLvoid*				data_[BUFFER_COUNT];
			GLsizeiptr			begin_[BUFFER_COUNT];
			GLsizeiptr			end_[BUFFER_COUNT];
			GLsizeiptr			size_[BUFFER_COUNT];
			GLsizeiptr			size_array_[BUFFER_COUNT];


			void			bufferData(BUFFER* buffer)
			{
				neb::gfx::ogl::bufferData(
						BUFFER::target_,
						buffer->buffer_,
						BUFFER::datasize_,
						size(),
						(GLvoid** const)data(),
						BUFFER::usage_,
						BUFFER_COUNT
						);
			}
			void			bufferSubData(BUFFER* buffer)
			{

				//LOG(lg, neb::gfx::sl, debug) << "update " << b << " to " << e;

				neb::gfx::ogl::bufferSubData(
						BUFFER::target_,
						buffer->buffer_,
						begin(),
						end(),
						BUFFER::datasize_,
						size(),
						(GLvoid** const)data(),
						BUFFER_COUNT
						);

			}
			void			bufferDataNull(BUFFER* buffer)
			{

				neb::gfx::ogl::bufferDataNull(
						BUFFER::target_,
						buffer->buffer_,
						BUFFER::datasize_,
						size_array(),
						BUFFER::usage_,
						BUFFER_COUNT
						);

			}
			void			drawElements(
					neb::gfx::glsl::program::base const * const & p,
					neb::core::pose const & pose,
					glm::vec3 scale)
			{

				// initialize buffers if not already
				auto it = buffers_.find(p);

				BUFFER* b;

				if(it == buffers_.end())
				{	
					//init_buffer(p);

					b = new BUFFER();
					b->init(p);
					bufferData(b);
				}
				else
				{
					b = it->second;
				}

				drawElements(p, b, pose, scale);

			}
			void			drawElements(
					neb::gfx::glsl::program::base const * const &	p,
					BUFFER*						b,
					neb::core::pose const &				pose,
					glm::vec3					scale,
					GLsizei						count)
			{
				LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;

				b->vertexAttribPointer();

				// load modelview matrix
				LOG(lg, neb::gfx::sl, debug) << "load modelview matrix";
				glm::mat4 model = pose.mat4_cast() * glm::scale(scale);

				assert(p->uniform_table_[neb::gfx::glsl::uniforms::MODEL] != -1);

				neb::gfx::ogl::glUniform(
						p->uniform_table_[neb::gfx::glsl::uniforms::MODEL],
						model
						);

				// bind
				LOG(lg, neb::gfx::sl, debug) << "bind vbo";
				b->bind();

				// draw
				LOG(lg, neb::gfx::sl, debug) << "draw";
				glDrawElements(
						GL_TRIANGLES,
						count,
						GL_UNSIGNED_SHORT,
						0);

				checkerror("glDrawElements");

				// unbind
				LOG(lg, neb::gfx::sl, debug) << "unbind vbo";
				b->unbind();
			}



		public:
			program_buffer_map			buffers_;


	};

}}}

#endif
