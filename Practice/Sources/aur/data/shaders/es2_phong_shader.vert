attribute vec4 position;
attribute vec4 color;
attribute vec3 normal;
attribute vec3 tangent;
attribute vec3 binormal;
attribute vec4 texture1_coordinates;
attribute vec4 texture2_coordinates;

uniform mat4 model_view_matrix;
uniform mat4 projection_matrix;
uniform mat3 normal_matrix;
uniform float point_size;

uniform bool texture1_enabled;
uniform bool texture1_transformation_enabled;
uniform mat4 texture1_transformation_matrix;
uniform bool texture1_normals_enabled;

uniform bool texture2_enabled;
uniform bool texture2_transformation_enabled;
uniform mat4 texture2_transformation_matrix;

varying vec4 fragment_view_position;
varying vec3 fragment_view_direction;
varying vec4 fragment_color;
varying vec2 fragment_texture1_coordinates;
varying vec2 fragment_texture2_coordinates;
varying vec3 fragment_view_normal;
varying mat3 fragment_view_tangent_binormal_normal;

void main()
{
    vec4 view_position = model_view_matrix * position;
    fragment_view_position = view_position;
    fragment_view_direction = -view_position.xyz;
    fragment_view_normal = normalize(normal_matrix * normal);
    fragment_view_tangent_binormal_normal =
        mat3(
            normalize(normal_matrix * tangent),
            normalize(normal_matrix * binormal),
            fragment_view_normal
        );

    fragment_color = color;
    if (texture1_enabled) {
        if (texture1_transformation_enabled) {
            vec4 transformed_texture1_coordinates = texture1_transformation_matrix * vec4(texture1_coordinates.st, 0.0, 1.0);
            fragment_texture1_coordinates = vec2(transformed_texture1_coordinates);
        } else {
            fragment_texture1_coordinates = vec2(texture1_coordinates);
        }
    }
    if (texture2_enabled) {
        if (texture2_transformation_enabled) {
            vec4 transformed_texture2_coordinates = texture2_transformation_matrix * vec4(texture2_coordinates.st, 0.0, 1.0);
            fragment_texture2_coordinates = vec2(transformed_texture2_coordinates);
        } else {
            fragment_texture2_coordinates = vec2(texture2_coordinates);
        }
    }

    gl_Position = projection_matrix * view_position;
    gl_PointSize = point_size;
}
