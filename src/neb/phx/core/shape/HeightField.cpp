#include <iostream>
#include <fstream>
#include <climits>
#include <ctime>

#include <neb/core/rand.hpp>
#include <neb/core/util/cast.hpp>
#include <neb/core/math/geo/vertex.hpp>

#include <neb/gfx/core/mesh.hh>

#include <neb/phx/core/shape/HeightField.hpp>
#include <neb/phx/core/actor/rigidactor/base.hpp>
#include <neb/phx/app/base.hpp>


typedef neb::phx::core::shape::HeightField THIS;

template<typename T, bool A = std::is_integral<T>::value, bool B = std::is_floating_point<T>::value> struct big {};

template<typename T> struct big<T, true, false>
{
	typedef long int type;
};
template<typename T> struct big<T, false, true>
{
	typedef T type;
};



template<typename T> struct HF
{

	HF(
			physx::PxU32 r,
			physx::PxU32 c
	  )
	{
		_M_r = r;
		_M_c = c;
	}
	void	alloc()
	{
		_M_z = new T[_M_r * _M_c];
	}
	void	createRandom()
	{
		alloc();

		srand(time(NULL));

		for(unsigned int i = 0; i < _M_r; i++)
		{
			for(unsigned int j = 0; j < _M_c; j++)
			{
				_M_z[at(i,j)] = (T)myrand();
			}
		}

	}
	T const		min() const
	{
		T m = std::numeric_limits<T>::max();

		for(unsigned int i = 0; i < _M_r; i++)
		{
			for(unsigned int j = 0; j < _M_c; j++)
			{
				T s = _M_z[at(i,j)];
				if(s < m) m = s;
			}
		}
		return m;
	}
	T const		max() const
	{
		T m = std::numeric_limits<T>::min();

		for(unsigned int i = 0; i < _M_r; i++)
		{
			for(unsigned int j = 0; j < _M_c; j++)
			{
				T s = _M_z[at(i,j)];
				if(s > m) m = s;
			}
		}
		return m;
	}
	int	at(int i, int j) const
	{
		i = (i + _M_r) % _M_r;
		j = (j + _M_c) % _M_c;
		return i * _M_c + j;
	}
	void	filterc(float factor)
	{
		//int n = (width * 2 + 1) * (width * 2 + 1);

		int width = _M_r / 2;
		int a = -width;
		int b = width + 1;

		T sum;
		T den;

		for(unsigned int i = 0; i < _M_r; i++)
		{
			for(unsigned int j = 0; j < _M_c; j++)
			{
				sum = 0;
				den = 0;
				for(int k = a; k < b; k++)
				{
					for(int l = a; l < b; l++)
					{
						T dist = sqrt(float(k*k) + float(l*l)) * factor;
						sum += _M_z[at(i + k, j + l)] * exp(-dist);
						den += exp(-dist);

						//std::cout<< " k,l = " << k << " " << l<< " dist = " << dist<< std::endl;
							
					}
				}
				//short oldS = _M_z[at(i,j)].height;
				T newS = sum / den;
			/*	std::cout
					<< " newS = " << newS
					<< " sum = " << sum
					<< " den = " << den
					<< std::endl;*/

				_M_z[at(i,j)] = newS;
			}
		}
	}
	void	filter(physx::PxU32 width)
	{
		int n = (width * 2 + 1) * (width * 2 + 1);

		int a = -width;
		int b = width + 1;

		T sum;

		for(unsigned int i = 0; i < _M_r; i++)
		{
			for(unsigned int j = 0; j < _M_c; j++)
			{
				sum = 0;
				for(int k = a; k < b; k++)
				{
					for(int l = a; l < b; l++)
					{
						sum += _M_z[at(i + k, j + l)];
					}
				}
				//short oldS = _M_z[at(i,j)].height;
				T newS = sum / (T)n;
				/*std::cout
				  << " oldS = " << oldS
				  << " newS = " << newS
				  << " sum = " << sum
				  << " n = " << n
				  << std::endl;*/
				_M_z[at(i,j)] = newS;
			}
		}
	}
	void	normalize(T a, T b)
	{
		T minH = min();
		T maxH = max();

		T slope = (b - a) / (maxH - minH);

		for(unsigned int i = 0; i < _M_r; i++)
		{
			for(unsigned int j = 0; j < _M_c; j++)
			{
				T& s = _M_z[at(i,j)];

				T l = slope * (s - minH) + a;

				/*	std::cout
					<< " s = " << s
					<< " l = " << l
					<< " new = " << (short)l
					<< " slope = " << slope
					<< std::endl;*/
				s = (T)l;
			}
		}
	}
	T const		get(int i, int j) const
	{
		return _M_z[at(i,j)];
	}
	T		get(int i, int j)
	{
		return _M_z[at(i,j)];
	}

	void		operator+=(HF<T> const & hf)
	{
		assert(hf._M_r == _M_r);
		assert(hf._M_c == _M_c);

		for(unsigned int i = 0; i < _M_r; i++)
		{
			for(unsigned int j = 0; j < _M_c; j++)
			{
				_M_z[at(i,j)] += hf.get(i,j);
			}
		}
	}

	T*				_M_z;
	unsigned int			_M_r;
	unsigned int			_M_c;

	//short				_M_min;
	//short				_M_max;

	static_assert(std::is_floating_point<T>::value, "float point");

	void		slope(T dx, T dy)
	{
		_M_dzdx = new T[_M_r*_M_c];
		_M_dzdy = new T[_M_r*_M_c];

		for(physx::PxU32 i = 0; i < _M_r; i++)
		{
			for(physx::PxU32 j = 0; j < _M_c; j++)
			{

				if(i == 0)
				{
					_M_dzdx[at(i,j)] = 
						(
						 _M_z[(i+1)*_M_c + j] -
						 _M_z[(i+0)*_M_c + j]
						) / dx;
				}
				else if(i == (_M_r-1))
				{
					_M_dzdx[at(i,j)] = 
						(
						 _M_z[(i-0)*_M_c + j] -
						 _M_z[(i-1)*_M_c + j]
						) / dx;
				}
				else
				{
					_M_dzdx[at(i,j)] = 
						(
						 _M_z[(i+1)*_M_c + j] -
						 _M_z[(i-1)*_M_c + j]
						) / dx / 2.0;
				}
				if(j == 0)
				{
					_M_dzdy[at(i,j)] = 
						(
						 _M_z[(i)*_M_c + j+1] -
						 _M_z[(i)*_M_c + j]
						) / dy;
				}
				else if(j == (_M_c-1))
				{
					_M_dzdy[at(i,j)] = 
						(
						 _M_z[(i)*_M_c + j] -
						 _M_z[(i)*_M_c + j-1]
						) / dy;
				}
				else
				{
					_M_dzdy[at(i,j)] = 
						(
						 _M_z[(i)*_M_c + j+1] -
						 _M_z[(i)*_M_c + j-1]
						) / dy / 2.0;
				}

			}
		}
	}

	T*		_M_dzdx;
	T*		_M_dzdy;
};

typedef neb::phx::core::shape::HeightField THIS;

neb::phx::core::shape::HeightField::HeightField()
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;
}
void				neb::phx::core::shape::HeightField::init(THIS::parent_t * const & p)
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;

	setParent(p);

	neb::core::core::shape::base::init(p);
	neb::gfx::core::shape::base::init(p);
	neb::phx::core::shape::base::init(p);

	create_physics();
}
void				neb::phx::core::shape::HeightField::release()
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	neb::core::core::shape::base::release();
	neb::gfx::core::shape::base::release();
	neb::phx::core::shape::base::release();


}
void				neb::phx::core::shape::HeightField::step(gal::etc::timestep  const & ts)
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;

}
void				neb::phx::core::shape::HeightField::create_physics()
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;

	auto actor = neb::could_be<parent_t, neb::phx::core::actor::base>(getParent());
	assert(actor);

	if(actor) {
		auto rigidactor = actor->isPxActorRigidActorBase();//std::dynamic_pointer_cast<neb::core::actor::Rigid_Actor>(parent_.lock());

		assert(rigidactor);

		if(rigidactor) {
			assert(rigidactor->px_actor_);

			auto px_rigidactor = rigidactor->px_actor_->isRigidActor();
			assert(px_rigidactor);

			physx::PxMaterial* px_mat[2];
			px_mat[0] = phx::app::base::global()->px_physics_->createMaterial(1,1,1);
			px_mat[1] = phx::app::base::global()->px_physics_->createMaterial(1,1,1);

			px_shape_ = px_rigidactor->createShape(*(to_geo()), px_mat, 2);
		}
	}

}


float scale(float x, float oa, float ob, float na, float nb)
{
	return (x - oa) / (ob - oa) * (nb - na) + na;
}

physx::PxGeometry*		neb::phx::core::shape::HeightField::to_geo() {

	unsigned int r = 51;
	unsigned int c = 51;
	float heightScale = 5.0 / float(SHRT_MAX);
	float rowScale = 30.0 / float(r-1);
	float colScale = 30.0 / float(c-1);

	unsigned int nbVerts = r * c;

	auto thePhysics = phx::app::base::global()->px_physics_;
	assert(thePhysics);

	// create heightfield short data

	HF<float> hf(r, c);
	hf.createRandom();


	//hf.filter(5);
	//hf.normalize(-10,10);
	//hf.normalize(-2.5,2.5);
	hf.filterc(desc_.f1);
	hf.normalize(-2.5,2.5);
	
	hf.filterc(desc_.f2);
	hf.normalize(-2.5,2.5);


	//assert(0);
	//
	// create physx data

	physx::PxHeightFieldSample* samples = new physx::PxHeightFieldSample[r * c];

	for(unsigned int i = 0; i < r; i++)
	{
		for(unsigned int j = 0; j < c; j++)
		{
			samples[i * c + j].height = (short)scale(hf.get(i,j), -2.5, 2.5, float(SHRT_MIN), float(SHRT_MAX));
			samples[i * c + j].materialIndex0 = physx::PxBitAndByte(0,0);
			samples[i * c + j].materialIndex1 = physx::PxBitAndByte(1,0);
		}
	}

	physx::PxHeightFieldDesc hfDesc;
	hfDesc.format             = physx::PxHeightFieldFormat::eS16_TM;
	hfDesc.nbColumns          = c;
	hfDesc.nbRows             = r;
	hfDesc.thickness          = -10.0f;
	hfDesc.samples.data       = samples;
	hfDesc.samples.stride     = sizeof(physx::PxHeightFieldSample);

	physx::PxHeightField* aHeightField = thePhysics->createHeightField(hfDesc);


	physx::PxHeightFieldGeometry* hfGeom = new physx::PxHeightFieldGeometry(
			aHeightField,
			physx::PxMeshGeometryFlags(),
			heightScale,
			rowScale,
			colScale);

	//PxShape* aHeightFieldShape = aHeightFieldActor->createShape(hfGeom, aMaterialArray, nbMaterials);



	unsigned int nbTriangles = (r - 1) * (c - 1) * 2;
	unsigned int nbIndices = nbTriangles * 3;
	math::geo::vertex* vertices = new math::geo::vertex[nbVerts];
	GLushort* indices = new GLushort[nbIndices];


	// for fun

	HF<float> hf2(r,c);
	hf2.createRandom();
	hf2.filter(5);

	min_y_ = hf.min();
	max_y_ = hf.max();


	// create gfx mesh

	hf.slope(rowScale, colScale);

	for(physx::PxU32 i = 0; i < r; i++)
	{
		for(physx::PxU32 j = 0; j < c; j++)
		{
			vertices[i * c + j].p = glm::vec3(
					float(i) * rowScale,
					hf.get(i,j),
					float(j) * colScale
					);


			glm::vec3 g(
					1,
					hf._M_dzdx[i*c+j] + hf._M_dzdy[i*c+j],
					1
				   );

			glm::vec3 y(0,1,0);

			glm::vec3 t = glm::cross(g,y);

			glm::vec3 n = glm::normalize(glm::cross(t,g));

			vertices[i * c + j].n = n;

		}
	}



	for(physx::PxU32 i = 0; i < (r-1); i++)
	{
		for(physx::PxU32 j = 0; j < (c-1); j++)
		{
			unsigned int d = (i * (c-1) + j) * 6;

			assert((d+5) < nbIndices);

			indices[d+0] = (i)   * c + j;
			indices[d+1] = (i+1) * c + j;
			indices[d+2] = (i)   * c + j + 1;

			indices[d+3] = (i+1) * c + j;
			indices[d+4] = (i+1) * c + j + 1;
			indices[d+5] = (i)   * c + j + 1;
		}
	}

	mesh_.reset(new neb::gfx::mesh::tri1);

	mesh_->setVerts(vertices, nbVerts);
	mesh_->setIndices(indices, nbIndices);

	return hfGeom;
}
void	THIS::load(ba::polymorphic_iarchive & ar, unsigned int const &)
{
}
void	THIS::save(ba::polymorphic_oarchive & ar, unsigned int const &) const
{
}
void			THIS::drawHF(
		neb::gfx::glsl::program::base const * const & p,
		neb::core::pose const & pose)
{
	auto npose = pose * pose_;

	p->use();

	neb::gfx::ogl::glUniform(p->uniform_table_[neb::gfx::glsl::uniforms::HF_MIN], min_y_);
	neb::gfx::ogl::glUniform(p->uniform_table_[neb::gfx::glsl::uniforms::HF_MAX], max_y_);

	draw_elements(p, npose);
}



