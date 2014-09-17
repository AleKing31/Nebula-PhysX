#version 130

in vec3 vs_mv_N;
in vec3 vs_N;

out vec4 color;

void main(void)
{
	

	vec3 n = vs_N.xzy;
	
	n.x = -n.x;
	//n.y = -n.y;
	//n.z = -n.z;

	color = vec4((n + 1.0) * 0.5, 1.0);
}



