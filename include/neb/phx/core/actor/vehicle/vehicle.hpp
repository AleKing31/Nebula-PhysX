#ifndef __NEBULA_ACTOR_VEHICLE_H__
#define __NEBULA_ACTOR_VEHICLE_H__

namespace neb { namespace phx { namespace core { namespace actor {

	class vehicle: public neb::phx::core::actor::base
	{
		public:

			physx::PxVehicleDrive4W* px_vehicle_drive_;

	};

}}}}

#endif

