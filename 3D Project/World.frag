#version 330 core

/**
\file PhongMultipleLightsAndTexture.glsl

\brief Fragment shader that calculates Phong lighting for each fragment,
textual for the same fragment and combines the two.

\param [in] position --- vec4 vertex position from memory.

\param [in] color --- vec4 vertex color from memory.

\param [in] normal --- vec3 normal vector from memory.

\param [in] tex_coord --- vec2 texture coordinate from memory.

\param [out] fColor --- vec4 output color to the frame buffer.

\param [uniform] Lt --- Light struct containing a single light attribute set.

\param [uniform] Mat --- Material struct containing a single material attribute set.

\param [uniform] eye --- vec3 position of the viewer/camera.

\param [uniform] GlobalAmbient --- vec4 global ambient color vector.

\param [uniform] useTexture --- boolean that determines if the texture is used.

\param [uniform] textrans --- mat4 texture transformation.

\param [uniform] tex1 --- sampler2D, the texture.

*/


struct Light
{
    bool on;             ///< Light on or off.
    vec4 position;       ///< Position of the light.
    vec3 spotDirection;  ///< Direction of the spot light.
    vec4 ambient;        ///< Ambient color of the light.
    vec4 diffuse;        ///< Diffuse color of the light.
    vec4 specular;       ///< Specular color of the light.
    float spotCutoff;    ///< Spot cutoff angle.
    float spotExponent;  ///< Spot falloff exponent.
    vec3 attenuation;    ///< Attenuation vector, x = constant, y = linear, z = quadratic.
};

struct Material
{
    sampler2D diffuse;	///< Diffuse map.
	sampler2D specular; ///< Specular map.
    vec4 emission;    	///< Emission color of the material.
    float shininess;  	///< Shininess exponent of the material.
};

in vec4 position;
in vec4 color;
in vec3 normal;
in vec2 tex_coord;

uniform Light Lt[20];
uniform Material Mat;
uniform vec3 eye;
uniform vec4 GlobalAmbient;
uniform int numLights;
uniform bool useLighting;
uniform bool fullbright;
uniform mat4 textrans;

layout (location = 0) out vec4 fColor;
layout (location = 1) out vec4 bColor;

void main()
{
    float deg = 0.017453292519943296;

    vec4 cc = vec4(0.0);
    vec4 globalAmbientPortion = GlobalAmbient;

	if (useLighting)
	{
		if (fullbright)
		{
			cc = texture(Mat.diffuse, tex_coord);
		}
		else if (length(Mat.emission) > 0.0f)
		{
			cc = vec4(texture(Mat.diffuse, tex_coord).xyz * min(vec3(1.0), Mat.emission.xyz*5), 1);
		}
		else
		{
			bool anylight = false;
			for (int i = 0; i < numLights; i++)
			{
				if (Lt[i].on)
				{	
					anylight = true;
					
					vec3 n = normalize(normal);
					vec3 l = normalize(vec3(Lt[i].position)-vec3(position));
					vec3 v = normalize(eye-vec3(position));
					vec3 h = normalize(l + v);
					float lightDistance =length(vec3(Lt[i].position)-vec3(position));

					float dfang = max(0.0, dot(n, l));
					float specang = max(0.0, dot(n, h));
					
					float attenuation = 1.0 / (Lt[i].attenuation[0] +
											   Lt[i].attenuation[1] * lightDistance +
											   Lt[i].attenuation[2] * lightDistance * lightDistance);

					float spotCos = dot(l, -normalize(Lt[i].spotDirection));
					float SpotCosCutoff = cos(Lt[i].spotCutoff*deg);  // assumes that spotCutoff is in degrees

					float spotFactor = 1.0;
					if (spotCos < SpotCosCutoff && Lt[i].spotCutoff < 179.9)  // Only fade if a spotlight
					{
						float range = 1 + SpotCosCutoff;
						spotFactor = pow(1 - (SpotCosCutoff - spotCos)/range, Lt[i].spotExponent);
					}

					vec4 ambientPortion = texture(Mat.diffuse, tex_coord) * (Lt[i].ambient + GlobalAmbient);
					vec4 diffusePortion = texture(Mat.diffuse, tex_coord) * Lt[i].diffuse * dfang * attenuation * spotFactor;
					vec4 specularPortion = texture(Mat.specular, tex_coord) * Lt[i].specular * pow(specang, Mat.shininess) * attenuation * spotFactor * min(vec4(1.0), diffusePortion*5);

					cc += ambientPortion + diffusePortion + specularPortion;
				}
			}
			
			if (!anylight)
			{
				cc = texture(Mat.diffuse, tex_coord)  * GlobalAmbient;
			}
		}
		cc = min(cc * color, vec4(1.0));
	}
	else
	{
		cc = color;
	}

    fColor = cc;
	
	// Check whether fragment output is higher than threshold, if so output as brightness color
    float brightness = dot(fColor.rgb, vec3(0.5, 0.5, 0.5));
    if(brightness > 1.0)
        bColor = vec4(fColor.rgb, 1.0);
}
