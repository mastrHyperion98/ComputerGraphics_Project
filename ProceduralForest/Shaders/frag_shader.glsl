#version 460 core

struct Material{
    vec3 color;
    sampler2D diffuseMap;
    bool isTextured;
    float shininess;
};

in vec3 FragPos;
in vec2 vertexUV;
in vec3 Normal;

out vec4 FragColor;

uniform Material material;
uniform bool enabled_textures;

void main()
{
    vec4 textureColor = texture(material.diffuseMap, vertexUV);
   if(!material.isTextured || !enabled_textures )
        FragColor =  vec4(material.color, 1.0);
   else {
        FragColor = textureColor;
   }
}
