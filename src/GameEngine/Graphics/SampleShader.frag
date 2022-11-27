#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec2 TexCoord;

uniform vec4 color;
uniform sampler2D texture1;

void main()
{  
    vec4 texColor = texture(texture1, TexCoord) * color;
    if(texColor.a < 0.3)
        discard;
    FragColor = texColor;
}
