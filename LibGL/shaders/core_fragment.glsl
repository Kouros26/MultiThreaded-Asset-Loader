#version 330 core

in vec2 TexCoord;
in vec3 normals;
in vec3 FragPos;

struct DirLight {
    vec3 direction;
	vec3 color;

    float ambient;
    float diffuse;
    float specular;
};


struct SpotLight {
    vec3 position;
    vec3 direction;
	vec3 color;

    float cutOff;
    float outerCutOff;

    float constant;
    float linear;
    float quadratic;

    float ambient;
    float diffuse;
    float specular;
};

struct PointLight {
    vec3 position;
	vec3 color;

    float constant;
    float linear;
    float quadratic;

    float ambient;
    float diffuse;
    float specular;
};

#define NR_POINT_LIGHTS_MAX 10
#define NR_SPOT_LIGHTS_MAX 10
#define NR_DIR_LIGHTS_MAX 10

#define SHINYNESS 8

uniform int NR_POINT_LIGHTS;
uniform int NR_SPOT_LIGHTS;
uniform int NR_DIR_LIGHTS;

uniform PointLight pointLights[NR_POINT_LIGHTS_MAX];
uniform DirLight dirLights[NR_DIR_LIGHTS_MAX];
uniform SpotLight spotLights[NR_SPOT_LIGHTS_MAX];
uniform vec3 viewPos;
uniform sampler2D ourTexture;

out vec4 fragment_color;

//Func

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = 0.0;
    vec3 halfwayDir = normalize(lightDir + viewDir);
    spec = pow(max(dot(normal, halfwayDir), 0.0), SHINYNESS);
    // attenuation
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance +
  			     light.quadratic * (distance * distance));
    // combine results
    float ambient  = light.ambient ;// * vec3(texture(texture1, TexCoords));
    float diffuse  = light.diffuse  * diff;//* vec3(texture(texture1, TexCoords));
    float specular = light.specular * spec;//* vec3(texture(texture1, TexCoords));
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular) * light.color;
}
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
     float spec = 0.0;
    vec3 halfwayDir = normalize(lightDir + viewDir);
    spec = pow(max(dot(normal, halfwayDir), 0.0), SHINYNESS);
    // combine results
    float ambient  = light.ambient ;//* vec3(texture(texture1, TexCoords));
    float diffuse  = light.diffuse  * diff;//* vec3(texture(texture1, TexCoords));
    float specular = light.specular * spec;//* vec3(texture(texture1, TexCoords));
    return (ambient + diffuse + specular) * light.color;
}

// calculates the color when using a spot light.
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), SHINYNESS);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    // spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    // combine results
    float ambient = light.ambient;//* vec3(texture(texture1, TexCoords));
    float diffuse = light.diffuse;// * diff* vec3(texture(texture1, TexCoords));
    float specular = light.specular * spec;//* vec3(texture(texture1, TexCoords));
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    return (ambient + diffuse + specular) * light.color;
}


void main()
{
    // properties
    vec3 norm = normalize(normals);
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 result;

    // phase 1: Directional lighting
    for(int i = 0; i < NR_DIR_LIGHTS; i++)
    	result += CalcDirLight(dirLights[i], norm, viewDir);

    // phase 2: Point lights
    for(int i = 0; i < NR_POINT_LIGHTS; i++)
        result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);

    // phase 3: Spot light
    for(int i = 0; i < NR_SPOT_LIGHTS; i++)
    	result += CalcSpotLight(spotLights[i], norm, FragPos, viewDir);

    fragment_color = texture(ourTexture, TexCoord) * vec4(result, 1.0);
}