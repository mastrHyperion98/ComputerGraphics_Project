#version 330 core

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
const int tex0 = 0;
const int tex1 = 1;
uniform Material material;
uniform bool enabled_textures = true;

void main()
{
    vec4 textureColor;
    int id = int(TextID);
    if(id == 0)
        textureColor = texture(material.diffuseMap[tex0], vertexUV);
    else
        textureColor = texture(material.diffuseMap[tex1], vertexUV);
   if(!material.isTextured || !enabled_textures )
        FragColor =  vec4(material.color, 1.0);
   else {
        FragColor = textureColor;
   }
}
