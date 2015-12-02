#version 150
uniform mat4 view;
uniform mat4 projection;
uniform vec2 tile_size;

in vec4 position;
in vec2 tile_id;

out vec2 tex_coord_out;

void main(void)
{
    gl_Position   = projection * view * vec4(position.x, position.y, 0.0, 1.0);
    tex_coord_out = vec2(position.z * tile_size.x + tile_size.x * float(tile_id.x), position.w * tile_size.y + tile_size.y * float(tile_id.y));
}
