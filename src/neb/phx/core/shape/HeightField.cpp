#include <iostream>
#include <fstream>
#include <climits>
#include <ctime>

#include <neb/core/util/cast.hpp>
#include <neb/core/math/geo/vertex.hpp>

//#include <neb/gfx/mesh/tri1.hpp>

#include <neb/phx/core/shape/HeightField/Base.hpp>
#include <neb/phx/core/actor/rigidactor/base.hpp>
#include <neb/phx/app/base.hpp>

#include <neb/core/math/HeightField.hpp>

typedef neb::phx::core::shape::HeightField::Base THIS;

THIS::Base()
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;
}
void				THIS::__init(THIS::parent_t * const & p)
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;

	create_physics();
}
void				THIS::step(gal::etc::timestep  const & ts)
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;

}
void				THIS::create_physics()
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;

	if(!neb::fnd::app::Base::is_valid()) return;

	auto actor = neb::could_be<parent_t, neb::phx::core::actor::base>(getParent());
	assert(actor);

	if(px_shape_) return;

	if(actor) {
		auto rigidactor = actor->isPxActorRigidActorBase();//std::dynamic_pointer_cast<neb::fnd::actor::Rigid_Actor>(parent_.lock());

		assert(rigidactor);

		if(rigidactor) {
			if(!rigidactor->px_actor_) rigidactor->create_physics();
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
physx::PxGeometry*		THIS::to_geo()
{
	unsigned int r = desc_.r;
	unsigned int c = desc_.c;

	float rowScale = desc_.w / float(r-1);
	float colScale = desc_.h / float(c-1);

	unsigned int nbVerts = r * c;
	
	assert(nbVerts <= (std::numeric_limits<unsigned short>::max() + 1));

	auto thePhysics = phx::app::base::global()->px_physics_;
	assert(thePhysics);

	// create heightfield short data

	neb::fnd::math::HeightField::Base hf(r, c);
	hf.createRandom();


	//for(float f : desc_.fc)
	//	hf.filterc(f);

	hf.normalize(-desc_.hs, desc_.hs);


	//assert(0);
	//
	// create physx data

	physx::PxHeightFieldSample* samples = new physx::PxHeightFieldSample[r * c];

	for(unsigned int i = 0; i < r; i++)
	{
		for(unsigned int j = 0; j < c; j++)
		{
			samples[i * c + j].height = (short)scale(hf.get(i,j), -desc_.hs, desc_.hs, float(SHRT_MIN), float(SHRT_MAX));
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
			desc_.hs / float(SHRT_MAX),
			rowScale,
			colScale);

	//PxShape* aHeightFieldShape = aHeightFieldActor->createShape(hfGeom, aMaterialArray, nbMaterials);

	// testing heightfield mipmap
	//neb::math::HeightField* hf2 = hf.mipmap(2);
	//mesh_from_heightfield(hf2, rowScale * 4, colScale * 4);


	//mesh_from_heightfield(&hf, rowScale, colScale);

	return hfGeom;

}
void	THIS::load(ba::polymorphic_iarchive & ar, unsigned int const &)
{
}
void	THIS::save(ba::polymorphic_oarchive & ar, unsigned int const &) const
{
}



