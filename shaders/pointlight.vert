#version 150


uniform	mat4 	projection;	// set for all vertices
uniform	mat4 	view;			// set for all vertices
uniform	mat4 	model;		// set for all vertices
uniform	float 	time;		// set for all vertices

uniform vec4 material_ambient;
uniform vec4 material_diffuse;
uniform vec4 material_specular;
uniform vec4 material_emissive;
uniform float material_shininess;

uniform struct {
	vec4 position;
	vec4 diffuse;
	vec4 specular;
	vec4 ambient;

	float constant_attenuation;
	float linear_attenuation;
	float quadratic_attenuation;
} light[2];

//uniform light light0;

in vec3 vertex;
in vec3 normal;
in vec2 uv;

out vec4 color;
out vec2 texCoord;

void main(void)
{
    vec3 normalized = vec3 (normalize(view * model * vec4(normal,0.0f)));
    vec4 pos = view * vec4(vertex, 1.0);

    //Find the eye vector (same as a directional light)
    vec3 E = -(pos.xyz);

    vec4 tempColor = vec4(0.0);
    for(int i = 0; i < 1; i++)
    {
        //Calculate the light position in eye space by multiplying by the modelview matrix
        vec3 lightPos = (view * light[i].position).xyz;

        //Get the light direction vector by finding the vector between the vertex and light position
        vec3 lightDir = (lightPos - pos.xyz).xyz;

        //The distance between the vertex and the light is the length of the light direction vector
        float dist = length(lightDir);

        //Find the angle between the normal and the light direction
        float lightDot = max(dot(normalized, lightDir.xyz), 0.0);

        //Assign the ambient color
        vec4 finalColor = material_ambient * light[i].ambient;

        if (lightDot > 0.0)
        {
            vec3 HV = normalize(lightPos + E);
            finalColor += material_diffuse * light[i].diffuse * lightDot;

            float NdotHV = max(dot(normalized, HV), 0.0);
            finalColor += material_specular * light[i].specular * pow(NdotHV, material_shininess);
        }

        //Calculate the attenuation factor
        float attenuation = 1.0 / (light[i].constant_attenuation +
                                     light[i].linear_attenuation * dist +
                                     light[i].quadratic_attenuation * dist * dist);

        //The material emissive value isn't affected by attenuation so that is added separately
        tempColor += (finalColor * attenuation);
    }

    color = material_emissive + tempColor;
    texCoord = uv;
    gl_Position = projection * view * model * vec4( vertex, 1.f );
}
