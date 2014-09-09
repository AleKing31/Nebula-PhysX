#include <iostream>
#include <iomanip>

#include <boost/serialization/vector.hpp>
#include <boost/serialization/shared_ptr.hpp>

#include <glm/gtx/transform.hpp>

#include <gal/log/log.hpp>

#include <neb/core/math/geo/polyhedron.hh>
#include <neb/core/math/geo/polygon.hpp>
#include <neb/core/util/debug.hpp>

#include <neb/gfx/free.hpp>
#include <neb/gfx/core/mesh.hh>
#include <neb/gfx/util/log.hpp>
#include <neb/gfx/glsl/program/threed.hpp>
#include <neb/gfx/glsl/attrib.hh>
#include <neb/gfx/glsl/uniform/scalar.hpp>
#include <neb/gfx/glsl/buffer/mesh.hpp>

neb::gfx::mesh::tri1::tri1() {
	//printf("%s\n",__PRETTY_FUNCTION__);
}
neb::gfx::mesh::tri1::~tri1() {
	//printf("%s\n",__PRETTY_FUNCTION__);
}
void	neb::gfx::mesh::tri1::construct(math::geo::polyhedron* poly) {

	std::cout << __PRETTY_FUNCTION__ << this << std::endl;

	assert(poly);

	math::geo::triangle* tris = poly->getTriangles();
	unsigned int nbTriangles = poly->getNbTriangles();
	
	assert(tris);

	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;
	LOG(lg, neb::gfx::sl, debug) << "tris: " << nbTriangles;


	nbVerts_   = 3 * nbTriangles;
	nbIndices_ = 3 * nbTriangles;
	vertices_  = new math::geo::vertex[nbVerts_];
	indices_   = new GLushort[nbIndices_];
		
	for(size_t i = 0; i < nbIndices_; ++i) {
		indices_[i] = i;
	}
	
	
	for(unsigned int i = 0; i < nbTriangles; i++)
	{
		for(unsigned int j = 0; j < 3; j++)
		{
			vertices_[i*3 + j] = *(tris[i].verts_[j]);
		}
	}

	LOG(lg, neb::gfx::sl, debug) << "vertices: " << nbVerts_;
	LOG(lg, neb::gfx::sl, debug) << "indices:  " << nbIndices_;


}
void			neb::gfx::mesh::tri1::setVerts(math::geo::vertex* verts, unsigned int nbVerts)
{
	vertices_ = verts;
	nbVerts_ = nbVerts;
}
void			neb::gfx::mesh::tri1::setIndices(GLushort* indices, unsigned int nbIndices)
{
	indices_ = indices;
	nbIndices_ = nbIndices;
}
unsigned int		neb::gfx::mesh::tri1::getNbIndices()
{
	return nbIndices_;
}
void		neb::gfx::mesh::tri1::serialize(boost::archive::polymorphic_iarchive & ar, unsigned int const & version) {
	
	printf("%s\n",__PRETTY_FUNCTION__);
	
	/*std::string filename = std::string(GLUTPP_OBJECT_DIR) + "/" + name;
	
	FILE * fp;
	
	std::cout << "load file " << filename << std::endl;

	fp = fopen(filename.c_str(), "rb");

	if (fp <= 0) {
		perror("fopen");
		abort();
	}*/
	
	//ar & vertices_;
	//ar & indices_;
	
	
	LOG(lg, neb::gfx::sl, info) << "vertices: " << nbVerts_;
	LOG(lg, neb::gfx::sl, info) << "indices:  " << nbIndices_;

}
void		neb::gfx::mesh::tri1::serialize(boost::archive::polymorphic_oarchive & ar, unsigned int const & version) {

	printf("%s\n",__PRETTY_FUNCTION__);
	
	//ar & vertices_;
	//ar & indices_;
	
	LOG(lg, neb::gfx::sl, info) << "vertices: " << nbVerts_;
	LOG(lg, neb::gfx::sl, info) << "indices:  " << nbIndices_;

}
void		neb::gfx::mesh::tri1::print(int sl) {
	LOG(lg, neb::gfx::sl, (severity_level)sl) << "mesh";

/*	for(auto v : vertices_) {
		v.print(sl);
	}	*/
}
/*
void			neb::gfx::mesh::tri1::init_buffer(
		program_shared p)
{
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;

	//glEnable(GL_TEXTURE_2D);

	if(nbIndices_ == 0) {
		printf("not initialized\n");
		assert(0);
		// return instead of abort so shape::base objects for making lights can pass through
		/// @todo need better system for this (like seperate mesh objects that implement this function!!
		return;
	}

	checkerror("unknown");

	auto buf(std::make_shared<neb::gfx::glsl::buffer::tri1>());
	buffers_[p.get()] = buf;

	buf->init(p);

	bufferData(buf);
}
*/
void			neb::gfx::mesh::tri1::drawElements(
		neb::gfx::glsl::program::base const * const & p,
		neb::core::pose const & pose,
		glm::vec3 scale)
{

	base_t::drawElements(p, pose, scale);


/*	// initialize buffers if not already
	if(!buffers_[p.get()])
	{	
		init_buffer(p);
	}
	auto buf = buffers_[p.get()];

	if(!buf) return;
	
	mesh_base::drawElements(p, buf, pose, scale);
*/

	/*
	// Uniforms
	// ========
	// material
	material_front_.load(p);

		// texture
		if(normal_map_) {
		LOG(lg, neb::gfx::sl, debug) << "activate normal map";
		glActiveTexture(GL_TEXTURE0);//checkerror("glActiveTexture");
		normal_map_->bind(context);
		p->get_uniform_scalar("normal_map")->load(0);

		p->get_uniform_scalar("has_normal_map")->load_b(true);
		} else {
		p->get_uniform_scalar("has_normal_map")->load_b(false);
		}

		if(texture_) {
		LOG(lg, neb::gfx::sl, debug) << "activate texture";
		glActiveTexture(GL_TEXTURE1);//checkerror("glActiveTexture");
		texture_->bind(context);
		p->get_uniform_scalar("texture")->load(1);

		p->get_uniform_scalar("has_texture")->load_b(true);
		} else {
		p->get_uniform_scalar("has_texture")->load_b(false);
		}
		*
*/

}
/*
void			neb::gfx::mesh::tri1::draw_elements(
		program_shared						p,
		std::shared_ptr<neb::gfx::glsl::buffer::tri1>		buf,
		neb::core::pose const & pose,
		glm::vec3 scale)
{
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;

	buf->vertexAttribPointer();
	// load modelview matrix
	LOG(lg, neb::gfx::sl, debug) << "load modelview matrix";
	mat4 model = pose.mat4_cast() * glm::scale(scale);

	assert(p->uniform_table_[neb::gfx::glsl::uniforms::MODEL] != -1);

	glUniformMatrix4fv(
			p->uniform_table_[neb::gfx::glsl::uniforms::MODEL],
			1,
			GL_FALSE,
			&model[0][0]
			);

	// bind
	LOG(lg, neb::gfx::sl, debug) << "bind vbo";
	buf->bind();

	// draw
	LOG(lg, neb::gfx::sl, debug) << "draw";
	glDrawElements(
			GL_TRIANGLES,
			nbIndices_,
			GL_UNSIGNED_SHORT,
			0);

	// unbind
	LOG(lg, neb::gfx::sl, debug) << "unbind vbo";
	buf->unbind();
}
*/
