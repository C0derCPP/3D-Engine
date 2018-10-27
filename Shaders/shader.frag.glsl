#version 450 core

struct Material
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shine;
};
struct Light
{
    vec3 direction;
    float cutOff;
    float outerCutOff;

    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
    float strength;
};

in vec3 vertexColor;
in vec2 Texcoord;
in vec3 fragPos;
in vec3 Normal;

in vec4 shadowCoord;

in vec3 reflected;
in vec3 refracted;
uniform samplerCube envMap;

layout(location = 0) out vec4 outcolor;

uniform sampler2D tex;
uniform vec3 viewPos;
uniform Material material;
uniform Light light;

const float blurSizeH = 1.0 / 300.0;
const float blurSizeV = 1.0 / 200.0;

void main()
{
    //float closestDepth = texture(tex, shadowCoord.xy).r;
    //float currentDepth = shadowCoord.z;

    float shadow = 1.0f;
    //if ( texture( shadowMap, (shadowCoord.xy/shadowCoord.w) ).z  <  (shadowCoord.z-0.005)/shadowCoord.w )
    //    shadow = 0.5;

    //ambient lighting
    vec3 ambient = light.ambient * material.ambient;

    //diffuse lighting
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(norm, lightDir), 0.0f) * shadow;
    vec3 diffuse = light.diffuse * (diff * material.diffuse);

    //specular lighting
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shine) * shadow;
    vec3 specular = light.specular * (spec * material.specular);

    //spotlight
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = (light.cutOff - light.outerCutOff);
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0f, 1.0f);

    if(intensity != 0)
    {
        diffuse *= intensity;
        specular *= intensity;
    }

    //attenuation
    float distance_ = length(light.position - fragPos);
    float attenuation = 1.0f / (light.constant + light.linear * distance_ + light.quadratic * (distance_ * distance_));

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    vec3 result = (ambient + diffuse + specular) * light.strength;

    if(result == vec3(0, 0, 0))
        outcolor = texture(tex, Texcoord) * vec4(vertexColor, 1.0);
    else
        outcolor = texture(tex, Texcoord) * vec4(result, 1.0);

    vec4 reflectedCol = texture(envMap, reflected);
    vec4 refractedCol = texture(envMap, refracted);
    vec4 envCol = mix(reflectedCol, refractedCol, 0.5f);
    //outcolor = mix(outcolor, reflectedCol, 0.8f) * vec4(vertexColor, 1.0);

}
