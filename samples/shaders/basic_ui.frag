#version 330 core

uniform Sampler2D texture_ui;
uniform float alpha;

in vec2 Tex;

void main() {
    gl_FragColor = vec4(texture(texture_ui, Tex) , alpha);
}
