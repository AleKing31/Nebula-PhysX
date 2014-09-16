// render the fragment normals as rgb color
// for use in generating normal maps

#version 130

out vec4	vs_mvp_N;

uniform mat4 view;
uniform mat4 proj;
uniform mat4 model;

in vec3		position;
in vec3		normal;

void main(void)
{
	mat4 mvp = proj * view * model;
	
	// Calculate view-space coordinate
	
	vs_mvp_N = normalize(mat3(mvp) * normal);

	// Calculate the clip-space position of each vertex
	gl_Position = mvp * vec4(position,1.0);
}


