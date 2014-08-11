#version 150

uniform sampler2D colorMap;

in vec4 color;
in vec2 texCoord;

out vec4 outColor;
out vec4 fragment_color;


void main(void) {
    outColor = color * texture( colorMap, texCoord.st );
}
