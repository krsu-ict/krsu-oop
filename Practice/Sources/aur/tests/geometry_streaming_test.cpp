#include "aur.hpp"

[[noreturn]]
int main(int argc, char **argv)
{
    using namespace aur;

    auto window = std::make_shared<SDLWindow>("aur");

    auto[plane_indices, plane_vertices] = geometry_generators::generate_plane_geometry_data(5.0f, 5.0f, 50, 50);
    auto plane_geometry = std::make_shared<ES2Geometry>(plane_indices, plane_vertices);
    auto plane_material = std::make_shared<ES2PhongMaterial>();
    plane_material->set_face_culling_enabled(false);
    auto[image1_data, image1_width, image1_height, image1_channels] = file_utilities::read_image_file("data/images/checkerboard.png");
    auto texture1 = std::make_shared<ES2Texture>(image1_data, image1_width, image1_height, image1_channels);
    plane_material->set_texture_1(texture1);
    auto plane = std::make_shared<Mesh>(plane_geometry, plane_material);
    plane->set_y(-0.5f);
    plane->set_rotation_x(-static_cast<float>(M_PI) * 0.5f);

    auto point_light = std::make_shared<PointLight>();
    point_light->set_intensity(0.5f);
    point_light->set_two_sided(true);
    point_light->set_y(0.5f);

    std::vector<std::shared_ptr<Object>> objects{plane};
    auto scene = std::make_shared<Scene>(objects);
    scene->get_point_lights().push_back(point_light);
    auto camera = scene->get_camera();
    camera->set_z(5.0f);

    float time = 0.0f;

    ES2Renderer renderer(scene, window);
    for (;;) {
        window->poll();

        auto &vertices = plane_geometry->get_vertices();
        for (auto &vertex : vertices) {
            vertex.position.z = (sinf(vertex.position.x + time) + cosf(vertex.position.y + time)) * 0.5f;
        }
        plane_geometry->set_requires_vertices_update(true);

        time += 0.01f;

        renderer.render();
    }
}
