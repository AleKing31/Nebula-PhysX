
#include <glm/gtx/transform.hpp>

#include <PxPhysicsAPI.h>

#include <neb/util/typedef.hpp>

#include <neb/phx/util/convert.hpp>



physx::PxVec2		phx::util::convert(vec2 const & v) {
	return physx::PxVec2(v.x, v.y);
}
physx::PxVec3		phx::util::convert(vec3 const & v) {
	return physx::PxVec3(v.x, v.y, v.z);
}
physx::PxVec4		phx::util::convert(vec4 const & v) {
	return physx::PxVec4(v.w, v.x, v.y, v.z);
}
physx::PxQuat		phx::util::convert(quat const & v) {
	return physx::PxQuat(v.w, v.x, v.y, v.z);
}

physx::PxMat44		phx::util::convert(mat4 const & v) {
	return physx::PxMat44((float*)&v[0]);
}

vec2			phx::util::convert(physx::PxVec2 const & v) {
	return vec2(v.x, v.y);
}
vec3			phx::util::convert(physx::PxVec3 const & v) {
	return vec3(v.x, v.y, v.z);
}
vec4			phx::util::convert(physx::PxVec4 const & v) {
	return vec4(v.w, v.x, v.y, v.z);
}
quat			phx::util::convert(physx::PxQuat const & v) {
	return quat(v.w, v.x, v.y, v.z);
}
mat4			phx::util::convert(physx::PxMat44 const & v) {
	return mat4(
			v[0][0],
			v[0][1],
			v[0][2],
			v[0][3],
			v[1][0],
			v[1][1],
			v[1][2],
			v[1][3],
			v[2][0],
			v[2][1],
			v[2][2],
			v[2][3],
			v[3][0],
			v[3][1],
			v[3][2],
			v[3][3]
		   );
}


mat4			phx::util::convert(physx::PxTransform const & t) {
	quat q(convert(t.q));
	vec3 p(convert(t.p));
	//mat4 ret(p,q);

	mat4 rot(glm::mat4_cast(q));
	mat4 tra(glm::translate(p));

	return rot * tra;
}


