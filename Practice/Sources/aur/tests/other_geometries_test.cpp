#include "aur.hpp"

[[noreturn]]
int main(int argc, char **argv)
{
    using namespace aur;

    auto window = std::make_shared<SDLWindow>("aur");

    auto[plane1_indices, plane1_vertices] = geometry_generators::generate_plane_geometry_data(1.0f, 1.0f, 2, 2);
    auto plane_geometry1 = std::make_shared<ES2Geometry>(plane1_indices, plane1_vertices);
    auto plane_material1 = std::make_shared<ES2ConstantMaterial>();
    plane_material1->set_emission_color(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
    plane_material1->set_face_culling_enabled(false);
    auto plane1 = std::make_shared<Mesh>(plane_geometry1, plane_material1);
    plane1->set_position(glm::vec3(-2.5f, 1.5f, 0.0f));

    auto[plane2_indices, plane2_vertices] = geometry_generators::generate_plane_geometry_data(1.0f, 1.0f, 10, 10);
    auto plane_geometry2 = std::make_shared<ES2Geometry>(plane2_indices, plane2_vertices);
    plane_geometry2->set_line_width(2.0f);
    plane_geometry2->set_type(Geometry::Type::LineStrip);
    auto plane_material2 = std::make_shared<ES2ConstantMaterial>();
    plane_material2->set_emission_color(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
    plane_material2->set_face_culling_enabled(false);
    auto plane2 = std::make_shared<Mesh>(plane_geometry2, plane_material2);
    plane2->set_position(glm::vec3(0.0f, 1.5f, 0.0f));

    auto[plane3_indices, plane3_vertices] = geometry_generators::generate_plane_geometry_data(1.0f, 1.0f, 20, 20);
    auto plane_geometry3 = std::make_shared<ES2Geometry>(plane3_indices, plane3_vertices);
    plane_geometry3->set_type(Geometry::Type::Points);
    auto plane_material3 = std::make_shared<ES2ConstantMaterial>();
    plane_material3->set_emission_color(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
    plane_material3->set_point_size(3.0f);
    plane_material3->set_face_culling_enabled(false);
    auto plane3 = std::make_shared<Mesh>(plane_geometry3, plane_material3);
    plane3->set_position(glm::vec3(2.5f, 1.5f, 0.0f));

    auto[circle1_indices, circle1_vertices] = geometry_generators::generate_circle_geometry_data(0.5f, 10);
    auto circle_geometry1 = std::make_shared<ES2Geometry>(circle1_indices, circle1_vertices);
    circle_geometry1->set_type(Geometry::Type::TriangleFan);
    auto circle_material1 = std::make_shared<ES2ConstantMaterial>();
    circle_material1->set_emission_color(glm::vec4(1.0f, 0.0f, 1.0f, 1.0f));
    circle_material1->set_face_culling_enabled(false);
    auto circle1 = std::make_shared<Mesh>(circle_geometry1, circle_material1);
    circle1->set_position(glm::vec3(-2.5f, 0.0f, 0.0f));

    auto[circle2_indices, circle2_vertices] = geometry_generators::generate_circle_geometry_data(0.5f, 25);
    auto circle_geometry2 = std::make_shared<ES2Geometry>(circle2_indices, circle2_vertices);
    circle_geometry2->set_line_width(2.0f);
    circle_geometry2->set_type(Geometry::Type::LineLoop);
    auto circle_material2 = std::make_shared<ES2ConstantMaterial>();
    circle_material2->set_emission_color(glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
    circle_material2->set_face_culling_enabled(false);
    auto circle2 = std::make_shared<Mesh>(circle_geometry2, circle_material2);
    circle2->set_position(glm::vec3(0.0f, 0.0f, 0.0f));

    auto[circle3_indices, circle3_vertices] = geometry_generators::generate_circle_geometry_data(0.5f, 50);
    auto circle_geometry3 = std::make_shared<ES2Geometry>(circle3_indices, circle3_vertices);
    circle_geometry3->set_type(Geometry::Type::Points);
    auto circle_material3 = std::make_shared<ES2ConstantMaterial>();
    circle_material3->set_emission_color(glm::vec4(0.0f, 1.0f, 1.0f, 1.0f));
    circle_material3->set_point_size(3.0f);
    circle_material3->set_face_culling_enabled(false);
    auto circle3 = std::make_shared<Mesh>(circle_geometry3, circle_material3);
    circle3->set_position(glm::vec3(2.5f, 0.0f, 0.0f));

    auto[sphere1_indices, sphere1_vertices] = geometry_generators::generate_sphere_geometry_data(0.5f, 10, 10);
    auto sphere_geometry1 = std::make_shared<ES2Geometry>(sphere1_indices, sphere1_vertices);
    sphere_geometry1->set_type(Geometry::Type::Triangles);
    auto sphere_material1 = std::make_shared<ES2ConstantMaterial>();
    sphere_material1->set_emission_color(glm::vec4(1.0f, 0.5f, 0.0f, 1.0f));
    sphere_material1->set_face_culling_enabled(false);
    auto sphere1 = std::make_shared<Mesh>(sphere_geometry1, sphere_material1);
    sphere1->set_position(glm::vec3(-2.5f, -1.5f, 0.0f));

    auto[sphere2_indices, sphere2_vertices] = geometry_generators::generate_sphere_geometry_data(0.5f, 20, 20);
    auto sphere_geometry2 = std::make_shared<ES2Geometry>(sphere2_indices, sphere2_vertices);
    sphere_geometry2->set_line_width(2.0f);
    sphere_geometry2->set_type(Geometry::Type::LineLoop);
    auto sphere_material2 = std::make_shared<ES2ConstantMaterial>();
    sphere_material2->set_emission_color(glm::vec4(1.0f, 0.0f, 0.5f, 1.0f));
    sphere_material2->set_face_culling_enabled(false);
    auto sphere2 = std::make_shared<Mesh>(sphere_geometry2, sphere_material2);
    sphere2->set_position(glm::vec3(0.0f, -1.5f, 0.0f));

    auto[sphere3_indices, sphere3_vertices] = geometry_generators::generate_sphere_geometry_data(0.5f, 30, 30);
    auto sphere_geometry3 = std::make_shared<ES2Geometry>(sphere3_indices, sphere3_vertices);
    sphere_geometry3->set_type(Geometry::Type::Points);
    auto sphere_material3 = std::make_shared<ES2ConstantMaterial>();
    sphere_material3->set_emission_color(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    sphere_material3->set_point_size(3.0f);
    sphere_material3->set_face_culling_enabled(false);
    auto sphere3 = std::make_shared<Mesh>(sphere_geometry3, sphere_material3);
    sphere3->set_position(glm::vec3(2.5f, -1.5f, 0.0f));

    std::vector<std::shared_ptr<Object>> objects{
        plane1, plane2, plane3,
        circle1, circle2, circle3,
        sphere1, sphere2, sphere3
    };
    auto scene = std::make_shared<Scene>(objects);
    auto camera = scene->get_camera();
    camera->set_z(5.0f);

    ES2Renderer renderer(scene, window);
    for (;;) {
        window->poll();

        static const float ROT_SPEED{0.01f};

        plane1->add_to_rotation_z(-ROT_SPEED);
        plane1->add_to_rotation_x(-ROT_SPEED);
        plane2->add_to_rotation_z(ROT_SPEED);
        plane2->add_to_rotation_x(ROT_SPEED);
        plane3->add_to_rotation_z(-ROT_SPEED);
        plane3->add_to_rotation_x(ROT_SPEED);

        circle1->add_to_rotation_z(-ROT_SPEED);
        circle1->add_to_rotation_x(-ROT_SPEED);
        circle2->add_to_rotation_z(ROT_SPEED);
        circle2->add_to_rotation_x(ROT_SPEED);
        circle3->add_to_rotation_z(-ROT_SPEED);
        circle3->add_to_rotation_x(ROT_SPEED);

        sphere1->add_to_rotation_z(-ROT_SPEED);
        sphere1->add_to_rotation_x(-ROT_SPEED);
        sphere2->add_to_rotation_z(ROT_SPEED);
        sphere2->add_to_rotation_x(ROT_SPEED);
        sphere3->add_to_rotation_z(-ROT_SPEED);
        sphere3->add_to_rotation_x(ROT_SPEED);

        renderer.render();
    }
}
