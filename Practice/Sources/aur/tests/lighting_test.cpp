#include "aur.hpp"

[[noreturn]]
int main(int argc, char **argv)
{
    using namespace aur;

    auto window = std::make_shared<SDLWindow>("aur");

    auto material = std::make_shared<ES2PhongMaterial>();
    material->set_specular_exponent(30.0f);

    auto[plane_indices, plane_vertices] = geometry_generators::generate_plane_geometry_data(500.0f, 500.0f, 10, 10);
    auto plane_geometry = std::make_shared<ES2Geometry>(plane_indices, plane_vertices);
    auto plane = std::make_shared<Mesh>(plane_geometry, material);
    plane->set_y(-2.0f);
    plane->set_rotation_x(-static_cast<float>(M_PI) * 0.5f);

    auto[sphere_indices, sphere_vertices] = geometry_generators::generate_sphere_geometry_data(1.0f, 100, 100);
    auto sphere_geometry = std::make_shared<ES2Geometry>(sphere_indices, sphere_vertices);
    auto sphere = std::make_shared<Mesh>(sphere_geometry, material);

    auto[lamp_indices, lamp_vertices] = geometry_generators::generate_sphere_geometry_data(0.2f, 20, 20);
    auto lamp_sphere_geometry = std::make_shared<ES2Geometry>(lamp_indices, lamp_vertices);
    auto lamp_material = std::make_shared<ES2ConstantMaterial>();
    lamp_material->set_emission_color(glm::vec4(1.0f));
    auto lamp1 = std::make_shared<Mesh>(lamp_sphere_geometry, lamp_material);
    auto lamp2 = std::make_shared<Mesh>(lamp_sphere_geometry, lamp_material);
    auto lamp3 = std::make_shared<Mesh>(lamp_sphere_geometry, lamp_material);
    auto spot_lamp_target = std::make_shared<Object>();

    std::vector<std::shared_ptr<Object>> objects{plane, sphere};
    auto scene = std::make_shared<Scene>(objects);
    auto camera = scene->get_camera();
    camera->set_y(5.0f);
    camera->set_z(10.0f);
    camera->set_rotation_x(-0.5f);

    auto point_light1 = std::make_shared<PointLight>();
    auto point_light2 = std::make_shared<PointLight>();
    point_light1->set_intensity(0.36f);
    point_light1->set_y(2.0f);
    point_light1->add_child(lamp1);
    point_light2->set_intensity(0.45f);
    point_light2->set_y(2.0f);
    point_light2->add_child(lamp2);
    scene->get_root()->add_child(point_light1);
    scene->get_root()->add_child(point_light2);
    scene->get_point_lights().push_back(point_light1);
    scene->get_point_lights().push_back(point_light2);

    static const float CAMERA_SPEED{0.1f};
    static const float CAMERA_ROT_SPEED{0.01f};
    static const glm::vec4 FORWARD{0.0f, 0.0f, 1.0f, 0.0f};
    static const float SPHERE_ROT_SPEED{0.05f};
    static const float INTENSITY_DIFF = 0.01f;
    static const float SPECULAR_EXPONENT_DIFF = 0.1f;

    window->set_on_key_down([&](int key) {
        switch (key) {
            case SDLK_w: camera->add_to_rotation_x(-CAMERA_ROT_SPEED); break;
            case SDLK_a: camera->add_to_rotation_y(CAMERA_ROT_SPEED); break;
            case SDLK_s: camera->add_to_rotation_x(CAMERA_ROT_SPEED); break;
            case SDLK_d: camera->add_to_rotation_y(-CAMERA_ROT_SPEED); break;
            case SDLK_e: camera->add_to_y(CAMERA_ROT_SPEED); break;
            case SDLK_q: camera->add_to_y(-CAMERA_ROT_SPEED); break;
            case SDLK_UP: camera->add_to_position(-glm::vec3(camera->get_model_matrix() * FORWARD * CAMERA_SPEED)); break;
            case SDLK_DOWN: camera->add_to_position(glm::vec3(camera->get_model_matrix() * FORWARD * CAMERA_SPEED)); break;
            case SDLK_7: point_light1->set_intensity(point_light1->get_intensity() + INTENSITY_DIFF); break;
            case SDLK_1: point_light1->set_intensity(point_light1->get_intensity() - INTENSITY_DIFF); break;
            case SDLK_8: point_light2->set_intensity(point_light2->get_intensity() + INTENSITY_DIFF); break;
            case SDLK_2: point_light2->set_intensity(point_light2->get_intensity() - INTENSITY_DIFF); break;
            case SDLK_9: material->set_specular_exponent(material->get_specular_exponent() + SPECULAR_EXPONENT_DIFF); break;
            case SDLK_3: material->set_specular_exponent(material->get_specular_exponent() - SPECULAR_EXPONENT_DIFF); break;
            case SDLK_ESCAPE: exit(0);
            default: break;
        }
    });

    float point_light_angle1 = 0.0f;
    float point_light_angle2 = 0.0f;
    float point_light_radius1 = 3.0f;
    float point_light_radius2 = 3.5f;

    ES2Renderer renderer(scene, window);
    for (;;) {
        window->poll();

        sphere->add_to_rotation_z(-SPHERE_ROT_SPEED);
        point_light1->set_x(cosf(point_light_angle1) * point_light_radius1);
        point_light1->set_z(sinf(point_light_angle1) * point_light_radius1);
        point_light2->set_x(cosf(point_light_angle2) * point_light_radius2);
        point_light2->set_z(sinf(point_light_angle2) * point_light_radius2);
        point_light_angle1 += 0.01f;
        point_light_angle2 -= 0.01f;

        renderer.render();
    }
}
