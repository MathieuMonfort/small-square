#version 330 core

uniform sampler2D texture_ui;
uniform float alpha;

in vec2 Tex;

out vec4 FragColor;
void main() {
    vec4 texColor =vec4(texture(texture_ui, Tex));
    if(texColor.a < 0.1e)
        discard;
    FragColor = texColor;

}
