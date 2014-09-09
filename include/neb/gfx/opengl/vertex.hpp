#ifndef NEB_GFX_OGL_VERTEX_HPP
#define NEB_GFX_OGL_VERTEX_HPP

#include <gal/stl/helper.hpp>

#include <GL/glew.h>

struct array_type {
	enum e {
		VEC2,
		VEC3,
		VEC4
	};
};

template<array_type::e T> struct array_traits {};
template<> struct array_traits<array_type::VEC2>
{
	static const GLint		size = 2;
	static const GLenum		type = GL_FLOAT;
	static const GLboolean		normalized = GL_FALSE;
	static const long		bytes = 8;
};
template<> struct array_traits<array_type::VEC3>
{
	static const GLint		size = 3;
	static const GLenum		type = GL_FLOAT;
	static const GLboolean		normalized = GL_FALSE;
	static const long		bytes = 12;
};


namespace neb { namespace gfx { namespace ogl {

	template<GLushort COUNT, array_type::e... A> void		vertexAttribPointer(
			const GLenum*		target,
			GLint*			index,
			/*		const GLint*		size,
					const GLenum*		type,
					const GLboolean*	normalized,*/
			const GLsizei*		stride,
			/*		GLvoid * const *	pointer,*/
			GLuint*			buffer,
			const unsigned int*	buffer_index,
			const GLuint*		divisor)
	{
		typedef typename gens<sizeof...(A)>::type seq_t;

		static const GLint size[] = { array_traits<A>::size... };
		GLenum type[] = { array_traits<A>::type... };
		GLboolean normalized[] = { array_traits<A>::normalized... };
		long bytes[] = { array_traits<A>::bytes... };

		long pointer = 0;

		for(unsigned int c = 0; c < COUNT; c++)
		{
			if(index[COUNT] != -1)
			{
				glBindBuffer(
						target[buffer_index[c]],
						buffer[buffer_index[c]]);

				checkerror("glBindBuffer");

				glEnableVertexAttribArray(
						index[c]);

				checkerror("glEnableVertexAttribArray %s\n", index[c]);

				glVertexAttribPointer(
						index[c],
						size[c],
						type[c],
						normalized[c],
						stride[c],
						(GLvoid*)pointer);

				checkerror("glVertexAttribPointer");

				glVertexAttribDivisor(
						index[c],
						divisor[c]);

				checkerror("glVertexAttribDivisor");

			}

			// advance pointer
			if(c < (COUNT - 1)) // not the last attribute
			{
				if(buffer[c] == buffer[c+1]) // next buffer is the same
				{
					pointer += bytes[c];
				}
				else
					pointer = 0;
			}

		}
	}
	void			bufferSubData(
			const GLenum*		target,
			GLuint*			buffer,
			GLintptr*		begin,
			GLintptr*		end,
			const GLsizeiptr*	datasize,
			GLsizeiptr*		size,
			GLvoid** const		data,
			unsigned int		count);

	void			bufferData(
			const GLenum*		target,
			const GLuint*		buffer,
			const GLsizeiptr*	datasize,
			const GLsizeiptr*	size,
			GLvoid** const		data,
			const GLenum*		usage,
			const unsigned int	count);

	void			bufferDataNull(
			const GLenum*		target,
			GLuint*			buffer,
			const GLsizeiptr*	datasize,
			GLsizeiptr*		size,
			const GLenum*		usage,
			unsigned int		count);

}}}



/*		
		vertexAttribPointer<A...>(
		seq_t(),
		target,
		index,
		stride,
		buffer,
		buffer_index,
		divisor,
		attrib_count);
		}
		template<array_type::e... A, int... S> void		vertexAttribPointer(
		seq<S...>,
		const GLenum*		target,
		GLint*			index,
		const array_type::e*	array_type,
		const GLsizei*		stride,
		GLuint*			buffer,
		const unsigned int*	buffer_index,
		const GLuint*		divisor,
		unsigned int		attrib_count)
		{
		pass(__vertexAttribPointer<A, S>(
		target,
		index,
		stride,
		buffer,
		buffer_index,
		divisor,
		attrib_count)...);
		}

		template<array_type::e A, int C> int		__vertexAttribPointer(
		const GLenum*		target,
		GLint*			index,
		const array_type::e*	array_type,
		const GLsizei*		stride,
		GLuint*			buffer,
		const unsigned int*	buffer_index,
		const GLuint*		divisor,
		unsigned int		attrib_count)
		{
//for(unsigned int c = 0; c < attrib_count; c++)
//{

if(index[C] != -1)
{
glBindBuffer(
target[buffer_index[C]],
buffer[buffer_index[C]]);

checkerror("glBindBuffer");

glEnableVertexAttribArray(
index[C]);

checkerror("glEnableVertexAttribArray %s\n", index[C]);

glVertexAttribPointer(
index[C],
array_traits<A>::size,
array_traits<A>::type,
array_traits<A>::normalized[C],
stride[C],
pointer[C]);

checkerror("glVertexAttribPointer");

glVertexAttribDivisor(
index[C],
divisor[C]);

checkerror("glVertexAttribDivisor");
}
//}
}


*/

#endif
