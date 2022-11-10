#version 400

#define MAX_LIGHTS 50

struct Light
{
	vec3 position;
	vec3 direction;
	vec4 color;
	float strength;
	int shiness;
	int type;
	float cutOff;
	
	//utlum
	float constant;
	float linear;
	float quadratic;
};

in vec4 ex_worldPosition;
in vec3 ex_worldNormal;
uniform mat4 viewMatrix;
uniform vec4 myColor;
uniform int shiness;
uniform float strength;
out vec4 out_Color;
uniform Light lights[MAX_LIGHTS];
uniform int currentLights;


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

float attenuation(float constant, float linear, float quadratic, float distance)
{
	float att = 1.0 / (constant + linear * distance + quadratic * distance * distance);
	return max(att, 0.0);
	//return att;
}

float distance(vec3 position, vec4 world_position)
{
	return length(position.xyz - world_position.xyz / world_position.w);
}

vec4 pointLight(Light light, vec3 world_normal, vec4 world_position, vec3 viewDirection, vec4 ambient)
{
	vec3 lightDirection = count_lightDirection(light.position, world_position);

	//difuzni slozka
	float diff_dot = count_dotProduct(lightDirection, world_normal);
	vec4 diffuse = count_diffuse(light.color, diff_dot);

	//spektakularni
	vec3 halfVector = count_halfVector(lightDirection, viewDirection);
	vec4 specular = count_specular(world_normal, light.shiness, light.strength, light.color, halfVector, diff_dot);

	//utlum
	float dis = distance(light.position, world_position);
	float att = attenuation(light.constant, light.linear, light.quadratic, dis);
	ambient *= att;
	diffuse *= att;
	specular *= att;

	vec4 tmp = ambient + diffuse + specular;
	return tmp;
}

vec4 directionalLight(Light light, vec3 world_normal, vec4 world_position, vec3 viewDirection, vec4 ambient)
{
	vec3 lightDirection = normalize(-light.direction);

	//difuzni
	float diff_dot = count_dotProduct(lightDirection, world_normal);
	vec4 diffuse = count_diffuse(light.color, diff_dot);

	//spektakularni
	vec3 halfVector = count_halfVector(lightDirection, viewDirection);
	vec4 specular = count_specular(world_normal, light.shiness, light.strength, light.color, halfVector, diff_dot);

	vec4 tmp = ambient + diffuse + specular;
	return tmp;
}

vec4 spotLight(Light light, vec3 world_normal, vec4 world_position, vec3 viewDirection, vec4 ambient, vec3 camera)
{
	vec3 lightDirection = count_lightDirection(camera, world_position);
	float theta = dot(lightDirection, normalize(-light.direction));
	if (theta <= light.cutOff)
	{
		return ambient;
	}

	//difuzni
	float diff_dot = count_dotProduct(lightDirection, world_normal);
	vec4 diffuse = count_diffuse(light.color, diff_dot);

	//spektakularni
	vec3 halfVector = count_halfVector(lightDirection, viewDirection);
	vec4 specular = count_specular(world_normal, light.shiness, light.strength, light.color, halfVector, diff_dot);

	float dis = distance(camera, world_position);
	float att = attenuation(light.constant, light.linear, light.quadratic, dis);
	diffuse *= att;
	specular *= att;

	vec4 tmp = ambient + diffuse + specular;
	return tmp;

}

void main() {
	vec3 world_normal = normalize(ex_worldNormal);
	vec4 color = myColor;
	vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);
	vec3 lightPosition = vec3(0.0, 0.0, 0.0);
	vec3 lightDirection = count_lightDirection(lightPosition, ex_worldPosition);
	vec3 camera = count_cameraPosition(viewMatrix);
	vec3 viewDirection = count_viewDirection(camera, ex_worldPosition);	

	vec4 fragmentColor = vec4(0.0, 0.0, 0.0, 0.0);

	for (int i = 0; i < currentLights; i++)
	{
		if(lights[i].type == 1)
			fragmentColor += pointLight(lights[i], world_normal, ex_worldPosition, viewDirection, ambient);
		else if (lights[i].type == 2)
		{
			fragmentColor += spotLight(lights[i], world_normal, ex_worldPosition, viewDirection, ambient, camera);
		}
			
		else if(lights[i].type == 3)
			fragmentColor += directionalLight(lights[i], world_normal, ex_worldPosition, viewDirection, ambient);
	}
	
	out_Color = fragmentColor;
}