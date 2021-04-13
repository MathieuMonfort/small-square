#version 330 core

uniform sampler2D texture_ui;
uniform float alpha;

in vec2 Tex;

out vec4 FragColor;
void main() {
    FragColor = vec4(texture(texture_ui, Tex).xyz,alpha) ;
}
