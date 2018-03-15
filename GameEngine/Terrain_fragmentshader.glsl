#version 430

out vec4 Fcolor;

in vec2 uv;
in vec3 SurfaceNormal;
in vec3 toLightVector;
in vec3 cameraPosition;

uniform sampler2D Texture;
uniform vec3 lightColour;
uniform float ShineDamper;
uniform float ReflectionScale;

void main()
{
vec3 unitNormal=normalize(SurfaceNormal);
vec3 unitToLightVector=normalize(toLightVector);
float nDot1=dot(unitNormal,unitToLightVector);
float brightness=max(nDot1,0.5);
vec3 diffuse=brightness*lightColour;


vec3 unitLightDirection=-unitToLightVector;
vec3 Reflactlight=reflect(unitLightDirection, unitNormal);
vec3 unitReflactlight=normalize(Reflactlight);
vec3 unitcameraPosition=normalize(cameraPosition);
  
float specularFactor=dot(unitcameraPosition,unitReflactlight);
specularFactor=max(specularFactor,0.3);
float DumpedFactor=pow(specularFactor,ShineDamper);
vec3 FinalSpecular=ReflectionScale*DumpedFactor*lightColour;


Fcolor = texture(Texture,uv);

};
