
#include <neb/gfx/mesh/tri1.hpp>

GLsizeiptr*			neb::gfx::mesh::tri1::begin()
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	begin_[0] = 0;
	begin_[1] = 0;
	return begin_;
}
GLsizeiptr*			neb::gfx::mesh::tri1::end()
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	end_[0] = indices_.size();
	end_[1] = nbVerts_;
	return end_;
}
GLvoid** const			neb::gfx::mesh::tri1::data()
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	std::cout << "vertices " << &vertices_[0] << std::endl;
	std::cout << "indices  " << &indices_[0] << std::endl;
	
	data_[0] = &indices_[0];
	data_[1] = &vertices_[0];
	return data_;
}
GLsizeiptr*			neb::gfx::mesh::tri1::size_array()
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	return size();
}
GLsizeiptr*			neb::gfx::mesh::tri1::size()
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	std::cout << "vertices " << nbVerts_ << std::endl;
	std::cout << "indices  " << indices_.size() << std::endl;

	assert(!nbVerts_ == 0);
	assert(indices_.size() > 0);

	size_[0] = indices_.size();
	size_[1] = nbVerts_;

	return size_;
}



