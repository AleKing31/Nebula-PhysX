#version 130

in vec3 vs_mvp_N;

out vec4 color;

void main(void)
{

	vec3 n = vec3(
			vs_mvp_N.x,
			-vs_mvp_N.y,
			-vs_mvp_N.z
		     );

	color = vec4((n + 1.0) * 0.5, 1.0);
}



