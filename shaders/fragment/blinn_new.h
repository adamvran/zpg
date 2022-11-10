#version 400
in vec4 ex_worldPosition;
in vec3 ex_worldNormal;
uniform mat4 viewMatrix;
uniform vec4 myColor;
uniform int shiness;
uniform float strength;
out vec4 out_Color;

float count_dotProduct(vec3 lightDirection, vec3 world_normal)
{
	return dot(lightDirection, world_normal);
}

vec4 count_diffuse(vec4 color, float diff_dotProduct)
{
	return max(diff_dotProduct, 0.0) * color;
}

vec3 count_halfVector(vec3 lightDirection, vec3 viewDirection)
{
	return normalize(lightDirection + viewDirection);
}

vec4 count_specular(vec3 world_normal, int shiness, float strength, vec4 color, vec3 halfVector, float diff_dotProduct)
{
	float fspec = pow(max(dot(halfVector, world_normal), 0.0), shiness);
	vec4 specular = strength * fspec * color;
	specular = diff_dotProduct <= 0.0 ? vec4(0, 0, 0, 0) : specular;
	return specular;
}

vec3 count_lightDirection(vec3 lightPosition, vec4 world_position)
{
	return normalize(vec3(lightPosition.xyz - world_position.xyz / world_position.w));
}

vec3 count_cameraPosition(mat4 viewMatrix)
{
	return vec3(inverse(viewMatrix)[3]); //z viewMatrix bereme pouze 4 sloupec a prenasobime = pozice kamery
}

vec3 count_viewDirection(vec3 camera, vec4 world_position)
{
	return normalize(vec3(camera.xyz - world_position.xyz / world_position.w));
}

void main() {
	vec3 world_normal = normalize(ex_worldNormal);
	vec4 color = myColor;
	vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);
	vec3 lightPosition = vec3(0.0, 0.0, 0.0);
	vec3 lightDirection = count_lightDirection(lightPosition, ex_worldPosition);
	vec3 camera = count_cameraPosition(viewMatrix);
	vec3 viewDirection = count_viewDirection(camera, ex_worldPosition);

	//difuzni slozka
	float diff_dotProduct = count_dotProduct(lightDirection, world_normal);
	vec4 diffuse = count_diffuse(color, diff_dotProduct);

	//pulici vektor
	vec3 halfVector = count_halfVector(lightDirection, viewDirection);
	vec4 specular = count_specular(world_normal, shiness, strength, color, halfVector, diff_dotProduct);

	out_Color = ambient + diffuse + specular;
}