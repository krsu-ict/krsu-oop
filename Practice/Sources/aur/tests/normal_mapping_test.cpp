#include "aur.hpp"

[[noreturn]]
int main(int argc, char **argv)
{
    using namespace aur;

    auto window = std::make_shared<SDLWindow>("aur", 0, 0);

    auto[plane1_indices, plane1_vertices] = geometry_generators::generate_plane_geometry_data(40, 40, 1, 1);
    auto plane1_geometry = std::make_shared<ES2Geometry>(plane1_indices, plane1_vertices);
    plane1_geometry->calculate_tangents_and_binormals();
    auto plane1_material = std::make_shared<ES2PhongMaterial>();
    auto[image1_data, image1_width, image1_height, image1_channels] = file_utilities::read_image_file("data/images/bricks.png");
    auto[image1_normals_data, image1_normals_width, image1_normals_height, image1_normals_channels] = file_utilities::read_image_file("data/images/bricks_normals.png");
    auto texture1 = std::make_shared<ES2Texture>(image1_data, image1_width, image1_height, image1_channels);
    auto texture1_normals = std::make_shared<ES2Texture>(image1_normals_data, image1_normals_width, image1_normals_height, image1_normals_channels);
    plane1_material->set_texture_1(texture1);
    plane1_material->set_texture_1_normals(texture1_normals);
    plane1_material->set_specular_exponent(50.0f);
    auto plane1 = std::make_shared<Mesh>(plane1_geometry, plane1_material);
    plane1->set_z(0);
    plane1->set_y(-10);
    plane1->set_rotation_x(-static_cast<float>(M_PI) * 0.5f);

    auto[lamp_indices, lamp_vertices] = geometry_generators::generate_sphere_geometry_data(0.2f, 20, 20);
    auto lamp_sphere_geometry = std::make_shared<ES2Geometry>(lamp_indices, lamp_vertices);
    auto lamp_material = std::make_shared<ES2ConstantMaterial>();
    lamp_material->set_emission_color(glm::vec4(1.0f));
    auto lamp1 = std::make_shared<Mesh>(lamp_sphere_geometry, lamp_material);
    auto lamp2 = std::make_shared<Mesh>(lamp_sphere_geometry, lamp_material);

    std::vector<std::shared_ptr<Object>> objects{plane1};
    auto scene = std::make_shared<Scene>(objects);

    auto point_light1 = std::make_shared<PointLight>();
    auto point_light2 = std::make_shared<PointLight>();
    point_light1->set_intensity(0.45f);
    point_light1->set_z(10.0f);
    point_light1->set_y(2.0f);
    point_light1->set_two_sided(true);
    point_light1->add_child(lamp1);
    point_light2->set_intensity(0.45f);
    point_light1->set_z(10.0f);
    point_light2->set_y(2.0f);
    point_light2->set_two_sided(true);
    point_light2->add_child(lamp2);
    scene->get_root()->add_child(point_light1);
    scene->get_root()->add_child(point_light2);
    scene->get_point_lights().push_back(point_light1);
    scene->get_point_lights().push_back(point_light2);

    auto camera = scene->get_camera();
    camera->set_z(8.0f);
    camera->set_position(glm::vec3(0.0f, 28.8816f, 22.6828f));
    camera->set_rotation(glm::vec3(-1.1f, 0.0f, 0.0f));

    static const float CAMERA_SPEED{0.3f};
    static const float CAMERA_ROT_SPEED{0.05f};
    static const float PLANE_ROT_SPEED{0.001f};

    static const glm::vec4 FORWARD{0.0f, 0.0f, 1.0f, 0.0f};

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
            case SDLK_ESCAPE: exit(0);
            default: break;
        }
    });

    bool plane1_rotation_enabled{false};
    glm::vec4 second_diffuse_color{plane1_material->get_diffuse_color()};
    bool texture1_enabled{true};
    bool texture1_normals_enabled{true};
    Texture::Mode texture1_texturing_mode{Texture::Mode::Modulation};
    Texture::FilterType texture1_magnification_filter_type{Texture::FilterType::Linear};
    Texture::FilterType texture1_minification_filter_type{Texture::FilterType::Linear};
    Texture::WrapMode texture1_wrap_mode_s{Texture::WrapMode::Repeat};
    Texture::WrapMode texture1_wrap_mose_t{Texture::WrapMode::Repeat};
    bool texture1_transformation_matrix_enabled{false};
    glm::mat4 texture1_transformation_matrix{1.0f};
    int texture1_anisotropy{0};
    bool texture1_mipmaps_enabled{true};

    float point_light_angle1 = 0.0f;
    float point_light_angle2 = 0.0f;
    float point_light_radius1 = 8.0f;
    float point_light_radius2 = 8.5f;

    ES2Renderer renderer(scene, window);
    for (;;) {
        window->poll();

        ImGui::SetNextWindowPos(ImVec2(10, 10));
        ImGui::Begin("Parameters", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove);
        {

            if (ImGui::CollapsingHeader("Texture Parameters ")) {
                ImGui::Checkbox("Rotate", &plane1_rotation_enabled);
                ImGui::ColorEdit4("Emission Color", glm::value_ptr(second_diffuse_color));

                ImGui::Checkbox("Enabled", &texture1_enabled);
                ImGui::Checkbox("Enable Normal Map", &texture1_normals_enabled);
                ImGui::Combo(
                    "Texturing Mode", reinterpret_cast<int *>(&texture1_texturing_mode),
                    "Addition\0Subtraction\0ReverseSubtraction\0Modulation\0Decaling\0"
                );
                ImGui::Combo(
                    "First Coordinate Wrap Mode", reinterpret_cast<int *>(&texture1_wrap_mode_s),
                    "Repeat\0Mirrored Repeat\0Clamp To Edge\0"
                );
                ImGui::Combo(
                    "Second Coordinate Wrap Mode", reinterpret_cast<int *>(&texture1_wrap_mose_t),
                    "Repeat\0Mirrored Repeat\0Clamp To Edge\0"
                );
                ImGui::Combo(
                    "Magnification Filter", reinterpret_cast<int *>(&texture1_magnification_filter_type),
                    "Nearest\0Linear\0Nearest Mipmap Nearest\0Nearest Mipmap Linear\0Linear Mipmap Nearest\0Linear Mipmap Linear\0"
                );
                ImGui::Combo(
                    "Minification Filter", reinterpret_cast<int *>(&texture1_minification_filter_type),
                    "Nearest\0Linear\0Nearest Mipmap Nearest\0Nearest Mipmap Linear\0Linear Mipmap Nearest\0Linear Mipmap Linear\0"
                );
                ImGui::Checkbox("Enable Transformation Matrix", &texture1_transformation_matrix_enabled);
                ImGui::InputFloat4("##5", glm::value_ptr(texture1_transformation_matrix), "%.2f");
                ImGui::InputFloat4("##6", glm::value_ptr(texture1_transformation_matrix) + 4, "%.2f");
                ImGui::InputFloat4("##7", glm::value_ptr(texture1_transformation_matrix) + 8, "%.2f");
                ImGui::InputFloat4("##8", glm::value_ptr(texture1_transformation_matrix) + 12, "%.2f");
                ImGui::SliderInt("Anisotropy", &texture1_anisotropy, 0, 16);
                ImGui::Checkbox("Use mipmaps", &texture1_mipmaps_enabled);
            }
        }
        ImGui::End();

        if (plane1_rotation_enabled) {
            plane1->add_to_rotation_y(PLANE_ROT_SPEED);
        }
        plane1_material->set_diffuse_color(second_diffuse_color);
        texture1->set_enabled(texture1_enabled);
        texture1_normals->set_enabled(texture1_normals_enabled);
        texture1->set_mode(texture1_texturing_mode);
        texture1->set_wrap_mode_s(texture1_wrap_mode_s);
        texture1_normals->set_wrap_mode_s(texture1_wrap_mode_s);
        texture1->set_wrap_mode_t(texture1_wrap_mose_t);
        texture1_normals->set_wrap_mode_t(texture1_wrap_mose_t);
        texture1->set_magnification_filter(texture1_magnification_filter_type);
        texture1_normals->set_magnification_filter(texture1_magnification_filter_type);
        texture1->set_minification_filter(texture1_minification_filter_type);
        texture1_normals->set_minification_filter(texture1_minification_filter_type);
        texture1->set_transformation_enabled(texture1_transformation_matrix_enabled);
        texture1->set_transformation_matrix(texture1_transformation_matrix);
        texture1->set_anisotropy(static_cast<float>(texture1_anisotropy));
        texture1_normals->set_anisotropy(static_cast<float>(texture1_anisotropy));
        texture1->set_mipmaps_enabled(texture1_mipmaps_enabled);
        texture1_normals->set_mipmaps_enabled(texture1_mipmaps_enabled);

        point_light1->set_x(cosf(point_light_angle1) * point_light_radius1);
        point_light1->set_z(sinf(point_light_angle1) * point_light_radius1);
        point_light2->set_x(cosf(point_light_angle2) * point_light_radius2);
        point_light2->set_z(sinf(point_light_angle2) * point_light_radius2);
        point_light_angle1 += 0.01f;
        point_light_angle2 -= 0.01f;

        renderer.render();
    }
}
