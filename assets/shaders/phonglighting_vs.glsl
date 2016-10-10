#version 420 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 tc;

uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 proj_matrix;

uniform vec3 light_pos = vec3(0, 0, 100);
uniform vec3 diffuse_albedo = vec3(0.5, 0.2, 0.7);
uniform vec3 ambient = vec3(0.1, 0.1, 0.1);

out VS_OUT {
	vec3 color;
} vs_out;

void main(void) {
	// build world-space light vector
	vec3 world_pos = (model_matrix * position).xyz;
	vec3 light_vec = normalize(light_pos - world_pos);

	// convert normal to world space
	vec3 world_norm = normalize(model_matrix * vec4(normal, 0)).xyz;

	float diffuse_factor = max(dot(light_vec, world_norm), 0);
	vec3 diffuse = diffuse_factor * diffuse_albedo;

	// color
	vs_out.color = ambient + diffuse;

	// position
	gl_Position = proj_matrix * view_matrix * model_matrix * position;
}