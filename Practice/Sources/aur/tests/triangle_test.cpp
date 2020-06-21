#include "aur.hpp"

[[noreturn]]
int main(int argc, char **argv)
{
    using namespace aur;

    auto window = std::make_shared<SDLWindow>("aur");

    auto[triangle_indices, triangle_vertices] = geometry_generators::generate_triangle_geometry_data(3.0f);
    triangle_vertices[0].color = glm::vec4{1.0f, 0.0f, 0.0f, 1.0f};
    triangle_vertices[1].color = glm::vec4{0.0f, 1.0f, 0.0f, 1.0f};
    triangle_vertices[2].color = glm::vec4{0.0f, 0.0f, 1.0f, 1.0f};
    auto triangle_geometry = std::make_shared<ES2Geometry>(triangle_indices, triangle_vertices);
    triangle_geometry->set_type(Geometry::Type::TriangleFan);
    auto triangle_material = std::make_shared<ES2ConstantMaterial>();
    triangle_material->set_face_culling_enabled(false);
    auto triangle = std::make_shared<Mesh>(triangle_geometry, triangle_material);

    std::vector<std::shared_ptr<Object>> objects{triangle};
    auto scene = std::make_shared<Scene>(objects);
    auto camera = scene->get_camera();
    camera->set_z(5.0f);

    ES2Renderer renderer(scene, window);
    for (;;) {
        window->poll();

        static const float TRIANGLE_ROT_SPEED{0.05f};
        triangle->add_to_rotation_z(-TRIANGLE_ROT_SPEED);

        renderer.render();
    }
}
