#version 400
in vec4 ex_worldPosition;
in vec3 ex_worldNormal;
uniform mat4 viewMatrix;
out vec4 out_Color;
void main() {
	vec3 world_normal = normalize(ex_worldNormal); //s délkou 1 to vrátí, to dělá to normalize
	vec4 color = vec4(1.0, 0.0, 0.0, 1.0);
	vec3 lightPosition = vec3(0.0, 0.0, 0.0);
	vec3 lightVector = normalize(vec3(lightPosition.xyz - ex_worldPosition.xyz / ex_worldPosition.w));
	float dot_product = dot(lightVector, world_normal);
	vec4 diffuse = max(dot_product, 0.0) * color;
	vec4 ambient = vec4 (0.1 ,0.1 ,0.1 ,1.0);

	float spec_strength = 1;
	vec3 camera_pos = vec3(inverse(viewMatrix)[3]);
	vec3 view_dir = normalize(vec3(camera_pos.x - ex_worldPosition.x, camera_pos.y - ex_worldPosition.y, camera_pos.z - ex_worldPosition.z));
        vec3 reflect_dir = reflect(-lightVector, world_normal);
	float spec = pow(max(dot(view_dir, reflect_dir), 0.0), 32);
	vec4 specular = spec_strength * spec * color;
        specular = dot_product <= 0.0 ? vec4(0, 0, 0, 0) : specular;

	out_Color = ambient + diffuse + specular;
}