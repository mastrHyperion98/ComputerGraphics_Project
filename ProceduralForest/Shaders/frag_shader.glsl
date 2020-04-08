#version 430 core

struct Material{
    vec3 color;
    sampler2D diffuseMap[2];
    bool isTextured;
    float shininess;
};

in vec3 FragPos;
in vec2 vertexUV;
in vec3 Normal;
in float TextID;
out vec4 FragColor;

uniform Material material;
uniform bool enabled_textures = true;

void main()
{
    int id = int(TextID);
    vec4 textureColor = texture(material.diffuseMap[id], vertexUV);
   if(!material.isTextured || !enabled_textures )
        FragColor =  vec4(material.color, 1.0);
   else {
        FragColor = textureColor;
   }
}
