#include <iostream>
#include <climits>


#include <neb/core/util/cast.hpp>
#include <neb/core/math/geo/vertex.hpp>

#include <neb/gfx/core/mesh.hh>

#include <neb/phx/core/shape/HeightField.hpp>
#include <neb/phx/core/actor/rigidactor/base.hpp>
#include <neb/phx/app/base.hpp>

struct HF
{
	HF(
			physx::PxHeightFieldSample* samples,
			physx::PxU32 nbRows,
			physx::PxU32 nbColumns
	      )
	{
		_M_samples = samples;
		_M_nbRows = nbRows;
		_M_nbColumns = nbColumns;
	}
	short	min()
	{
		short m = SHRT_MAX;
		
		for(unsigned int i = 0; i < _M_nbRows; i++)
		{
			for(unsigned int j = 0; j < _M_nbColumns; j++)
			{
				short s = _M_samples[at(i,j)].height;
				if(s < m) m = s;
			}
		}
		return m;
	}
	short	max()
	{
		short m = SHRT_MIN;
		
		for(unsigned int i = 0; i < _M_nbRows; i++)
		{
			for(unsigned int j = 0; j < _M_nbColumns; j++)
			{
				short s = _M_samples[at(i,j)].height;
				if(s > m) m = s;
			}
		}
		return m;
	}
	int	at(
			int i,
			int j
		  )
	{
		i = (i + _M_nbRows) % _M_nbRows;
		j = (j + _M_nbColumns) % _M_nbColumns;
		return i * _M_nbColumns + j;
	}
	void	filter(physx::PxU32 width)
	{
		int n = (width * 2 + 1) * (width * 2 + 1);
		
		int a = -width;
		int b = width + 1;

		long sum;
		
		for(unsigned int i = 0; i < _M_nbRows; i++)
		{
			for(unsigned int j = 0; j < _M_nbColumns; j++)
			{
				sum = 0;
				for(int k = a; k < b; k++)
				{
					for(int l = a; l < b; l++)
					{
						sum += _M_samples[at(i + k, j + l)].height;
					}
					//short oldS = _M_samples[at(i,j)].height;
					short newS = sum / n;
					/*std::cout
						<< " oldS = " << oldS
						<< " newS = " << newS
						<< " sum = " << sum
						<< " n = " << n
						<< std::endl;*/
					_M_samples[at(i,j)].height = newS;
				}
			}
		}
	}
	void	normalize()
	{
		short minH = min();
		short maxH = max();

		double slope = float(SHRT_MAX - SHRT_MIN) / float(maxH - minH);

		for(unsigned int i = 0; i < _M_nbRows; i++)
		{
			for(unsigned int j = 0; j < _M_nbColumns; j++)
			{
				short& s = _M_samples[at(i,j)].height;
				double l = slope * (s - maxH) + SHRT_MAX;
			/*	std::cout
					<< " s = " << s
					<< " l = " << l
					<< " new = " << (short)l
					<< " slope = " << slope
					<< std::endl;*/
				s = (short)l;
			}
		}
	}


	physx::PxHeightFieldSample*	_M_samples;
	unsigned int			_M_nbRows;
	unsigned int			_M_nbColumns;

	short				_M_min;
	short				_M_max;
};



neb::phx::core::shape::HeightField::HeightField(std::shared_ptr<neb::core::core::shape::util::parent> parent):
	gal::stl::child<neb::core::core::shape::util::parent>(parent.get())
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;
}
void				neb::phx::core::shape::HeightField::__init()
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;

}
void				neb::phx::core::shape::HeightField::init()
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	neb::core::core::shape::base::init();
	neb::gfx::core::shape::base::init();
	neb::phx::core::shape::base::init();

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
physx::PxGeometry*		neb::phx::core::shape::HeightField::to_geo() {

	unsigned int nbRows = 30;
	unsigned int nbCols = 30;
	float heightScale = 5.0 / float(SHRT_MAX);
	float rowScale = 1.0;
	float colScale = 1.0;

	unsigned int nbVerts = nbRows * nbCols;

	auto thePhysics = phx::app::base::global()->px_physics_;
	assert(thePhysics);

	physx::PxHeightFieldSample* samples = new physx::PxHeightFieldSample[nbRows*nbCols];

	for(unsigned int i = 0; i < nbRows; i++)
	{
		for(unsigned int j = 0; j < nbCols; j++)
		{
			samples[i * nbCols + j].height = (::rand() % USHRT_MAX) + SHRT_MIN;
			samples[i * nbCols + j].materialIndex0 = physx::PxBitAndByte(0,0);
			samples[i * nbCols + j].materialIndex1 = physx::PxBitAndByte(1,0);
		}
	}

	HF hf(samples, nbRows, nbCols);

	hf.filter(10);
	hf.normalize();
	hf.filter(2);

	//assert(0);

	physx::PxHeightFieldDesc hfDesc;
	hfDesc.format             = physx::PxHeightFieldFormat::eS16_TM;
	hfDesc.nbColumns          = nbCols;
	hfDesc.nbRows             = nbRows;
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



	unsigned int nbTriangles = (nbRows - 1) * (nbCols - 1) * 2;
	unsigned int nbIndices = nbTriangles * 3;
	math::geo::vertex* vertices = new math::geo::vertex[nbVerts];
	GLushort* indices = new GLushort[nbIndices];



	for(physx::PxU32 i = 0; i < nbRows; i++)
	{
		for(physx::PxU32 j = 0; j < nbCols; j++)
		{
			unsigned int c = j + (i*nbCols);

			vertices[i * nbCols + j].p = glm::vec3(
					physx::PxReal(i) * rowScale,
					physx::PxReal(samples[c].height) * heightScale,
					physx::PxReal(j) * colScale
					);

			float dydx;
			float dydz;
			if(i == 0)
			{
				dydx = 
					(
					 physx::PxReal(samples[(i+1)*nbCols + j].height) -
					 physx::PxReal(samples[(i+0)*nbCols + j].height)
					) * heightScale / rowScale;
			}
			else if(i == (nbRows-1))
			{
				dydx = 
					(
					 physx::PxReal(samples[(i-0)*nbCols + j].height) -
					 physx::PxReal(samples[(i-1)*nbCols + j].height)
					) * heightScale / rowScale;
			}
			else
			{
				dydx = 
					(
					 physx::PxReal(samples[(i+1)*nbCols + j].height) -
					 physx::PxReal(samples[(i-1)*nbCols + j].height)
					) * heightScale / rowScale / 2.0;
			}
			if(j == 0)
			{
				dydz = 
					(
					 physx::PxReal(samples[(i)*nbCols + j+1].height) -
					 physx::PxReal(samples[(i)*nbCols + j].height)
					) * heightScale / colScale;
			}
			else if(j == (nbCols-1))
			{
				dydz = 
					(
					 physx::PxReal(samples[(i)*nbCols + j].height) -
					 physx::PxReal(samples[(i)*nbCols + j-1].height)
					) * heightScale / colScale;
			}
			else
			{
				dydz = 
					(
					 physx::PxReal(samples[(i)*nbCols + j+1].height) -
					 physx::PxReal(samples[(i)*nbCols + j-1].height)
					) * heightScale / colScale / 2.0;
			}

			glm::vec3 g(1,1,dydx + dydz);
			glm::vec3 y(0,1,0);
			glm::vec3 t = glm::cross(g,y);
			glm::vec3 n = glm::normalize(glm::cross(t,g));


			vertices[i * nbCols + j].n = n;

		}
	}



	for(physx::PxU32 i = 0; i < (nbRows-2); i++)
	{
		for(physx::PxU32 j = 0; j < (nbCols-2); j++)
		{
			unsigned int d = (i * nbCols + j) * 6;

			assert((d+5) < nbIndices);

			indices[d+0] = (i)   * nbCols + j;
			indices[d+1] = (i+1) * nbCols + j;
			indices[d+2] = (i)   * nbCols + j + 1;

			indices[d+3] = (i+1) * nbCols + j;
			indices[d+4] = (i+1) * nbCols + j + 1;
			indices[d+5] = (i)   * nbCols + j + 1;
		}
	}

	mesh_.reset(new neb::gfx::mesh::tri1);

	mesh_->setVerts(vertices, nbVerts);
	mesh_->setIndices(indices, nbIndices);

	return hfGeom;
}



