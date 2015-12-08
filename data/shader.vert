#version 150
uniform mat4 view;
uniform mat4 projection;
uniform vec2 tile_size;

in vec4 position;
in vec2 tile_id;

out vec2 tex_coord_out;

void main(void)
{
    float center = 250.0;
    float scale = max(0.75, (center - position.y) / (2.0 * center));
    gl_Position   = projection * view * vec4(scale * position.x, scale * position.y - 0.6 * scale * position.y, 0.0, 1.0);
    tex_coord_out = vec2(position.z * tile_size.x + tile_size.x * float(tile_id.x), position.w * tile_size.y + tile_size.y * float(tile_id.y));
}
