#version 330 core

in vec2 vtexCoord;
out vec4 fragColor;

uniform sampler2D explosion;

uniform float time;
const float speed = 5;

void main()
{
    float slice = 1.0/2;
    int frame = int(mod(speed*time/slice, 48));
    float x = frame%8;
    float y = -(1+frame/8);
    
    vec2 texCoord = vtexCoord * vec2(1.0/8, 1.0/6);
    texCoord.x += x/8.0;
    texCoord.y += y/6.0;
    fragColor = texture(explosion, texCoord);
    fragColor *= fragColor.a;
}
