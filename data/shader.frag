#version 150

uniform sampler2D texture;
out vec4 frag_color;

in vec2 tex_coord_out;

void main(void)
{
    //frag_color = vec4(tex_coord_out.x, tex_coord_out.y, 0, 1);
    frag_color = texture2D(texture, tex_coord_out);
}
