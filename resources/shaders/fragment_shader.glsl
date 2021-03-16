#version 330 core

in vec2 out_uv;
in vec3 out_normal;
in vec3 fragmentPosition;

uniform sampler2D textureSampler;
uniform vec3 lightColour;
uniform vec3 lightPosition;
uniform vec3 viewPosition;

out vec4 fragmentColor;

void main() 
{
	// Ambient
	float ambientStrength = 1.0f;
	vec3 ambient = ambientStrength * lightColour;
	
	// Diffuse
	vec3 lightDirection = normalize(lightPosition - fragmentPosition);
	float diff = max(dot(normalize(out_normal), lightDirection), 0.0f);
	vec3 diffuse = diff * lightColour;
	
	// Specular
	float specularStrength = 0.5f;
	vec3 viewDir = normalize(viewPosition - fragmentPosition);
	vec3 reflection = reflect(-lightDirection, normalize(out_normal));
	float specular = pow(max(dot(viewDir, reflection), 0.0f), 32);
	
	// Texture
	vec3 textureColour = texture(textureSampler, out_uv).rgb;
	
	// Output
	fragmentColor = vec4((ambient + diffuse) * textureColour + specular, 1.0f);
}