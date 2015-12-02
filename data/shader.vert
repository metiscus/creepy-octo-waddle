#version 150
uniform mat4 view;
uniform mat4 projection;
uniform vec2 tile_size;

in vec4 position;
in uvec2 tile_id;

out vec2 tex_coord_out;

void main(void)
{
    gl_Position   = projection * view * vec4(position.x, position.y, 0.0, 1.0);
    // compute the texture coordinate of this point
    //tex_coord_out = vec2((float(tile_id.x) + 1.0) * tile_size.x + position.z, (float(tile_id.y) + 1.0) * tile_size.y + position.w);
    tex_coord_out = vec2(position.z * tile_size.x + tile_size.x * tile_id.x, position.w * tile_size.y + tile_size.y * tile_id.y);
}
