#version 430 core

const int TEXTURE_MAP_MAX = 2;
struct Material{
    vec3 color;
    sampler2D diffuseMap[TEXTURE_MAP_MAX];
    bool isTextured;
    float shininess;
};

in vec3 FragPos;
in vec2 vertexUV;
in vec3 Normal;
in float Offset;
out vec4 FragColor;

uniform Material material;

uniform bool enabled_textures = true;

void main()
{
    int diffuseOffset = int(Offset);
    vec4 textureColor = texture(material.diffuseMap[diffuseOffset], vertexUV);
   if(!material.isTextured || !enabled_textures )
        FragColor =  vec4(material.color, 1.0);
   else {
        FragColor = textureColor;
   }
}
