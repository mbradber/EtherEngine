#version 420 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 tc;

uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 proj_matrix;

uniform vec3 light_pos = vec3(0, 0, 100);
uniform vec3 diffuse_albedo = vec3(0.5, 0.2, 0.7);
uniform vec3 specular_albedo = vec3(0.7);
uniform float specular_power = 128.0;
uniform vec3 ambient = vec3(0.1, 0.1, 0.1);

out VS_OUT {
	vec3 color;
} vs_out;

void main(void) {
	mat4 mv_matrix = view_matrix * model_matrix;

	vec4 P = mv_matrix * position;
	vec3 N = (mv_matrix * vec4(normal, 0)).xyz;
	vec3 LP = (view_matrix * vec4(light_pos, 1)).xyz;
	vec3 L = LP - P.xyz;
	vec3 V = -P.xyz;

	N = normalize(N);
	L = normalize(L);
	V = normalize(V);

	vec3 R = reflect(-L, N);

	float diffuse_factor = max(dot(N, L), 0);
	vec3 diffuse = diffuse_factor * diffuse_albedo;

	float spec_factor = pow(max(dot(R, V), 0), specular_power);
	vec3 specular = spec_factor * specular_albedo;

	// color
	vs_out.color = ambient + diffuse + specular;

	// position
	gl_Position = proj_matrix * P;
}