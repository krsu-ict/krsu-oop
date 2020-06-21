#include "aur.hpp"

#include <cmath>
#include <chrono>

static float find_delta_time(std::chrono::high_resolution_clock::time_point &previous_time)
{
    auto time_now = std::chrono::high_resolution_clock::now();
    float delta_time = std::chrono::duration_cast<std::chrono::duration<float, std::deci>>(time_now - previous_time).count();
    previous_time = time_now;

    static const float max_delta_time = 0.66f;
    return glm::clamp(delta_time, 0.0f, max_delta_time);
}

[[noreturn]]
int main(int argc, char **argv)
{
    using namespace aur;

    auto window = std::make_shared<SDLWindow>("aur");
    // auto window = std::make_shared<SDLWindow>("aur", 1280, 720);

    // Floor

    auto[floor_indices, floor_vertices] = geometry_generators::generate_plane_geometry_data(5, 5, 1, 1);
    auto floor_geometry = std::make_shared<ES2Geometry>(floor_indices, floor_vertices);
    auto floor_material = std::make_shared<ES2PhongMaterial>();
    floor_material->set_specular_exponent(70.0f);
    auto[image1_data, image1_width, image1_height, image1_channels] = file_utilities::read_image_file("data/images/checkerboard.png");
    auto floor_texture = std::make_shared<ES2Texture>(image1_data, image1_width, image1_height, image1_channels);
    floor_material->set_texture_1(floor_texture);
    auto floor = std::make_shared<Mesh>(floor_geometry, floor_material);
    floor->set_y(-0.5f);
    floor->set_rotation_x(-static_cast<float>(M_PI) / 2.0f);

    // Enemy

    enum DemonState {
        Alive,
        Dying,
        Dead
    };
    auto[demon_indices, demon_vertices] = geometry_generators::generate_plane_geometry_data(1, 1, 1, 1);
    auto demon_geometry = std::make_shared<ES2Geometry>(demon_indices, demon_vertices);
    auto demon_material = std::make_shared<ES2ConstantMaterial>();
    auto[image2_data, image2_width, image2_height, image2_channels] = file_utilities::read_image_file("data/images/cacodemon.png");
    auto demon_texture = std::make_shared<ES2Texture>(image2_data, image2_width, image2_height, image2_channels);
    auto demon_texture_matrix = demon_texture->get_transformation_matrix();
    int demon_sprite_frame_count = 10;
    int demon_sprite_dying_first_frame = 4;
    float demon_sprite_size = 1.0f / (float) demon_sprite_frame_count;
    demon_texture_matrix[0][0] = demon_sprite_size;
    demon_texture->set_transformation_matrix(demon_texture_matrix);
    demon_texture->set_transformation_enabled(true);
    demon_texture->set_minification_filter(Texture::FilterType::Nearest);
    demon_texture->set_magnification_filter(Texture::FilterType::Nearest);
    demon_material->set_texture_1(demon_texture);
    demon_material->set_blending_enabled(true);
    demon_material->set_transparent(true);
    auto demon = std::make_shared<Mesh>(demon_geometry, demon_material);
    DemonState demon_state = Alive;
    Sphere demon_collision_sphere(demon->get_position() + glm::vec3(0.0f, 0.5f, 0.0f), 0.3f);

    // Player/Gun

    enum GunState {
        Idling,
        Shooting
    };
    auto[gun_indices, gun_vertices] = geometry_generators::generate_plane_geometry_data(1, 1, 1, 1);
    auto gun_geometry = std::make_shared<ES2Geometry>(gun_indices, gun_vertices);
    auto gun_material = std::make_shared<ES2ConstantMaterial>();
    auto[image3_data, image3_width, image3_height, image3_channels] = file_utilities::read_image_file("data/images/shotgun.png");
    auto gun_texture = std::make_shared<ES2Texture>(image3_data, image3_width, image3_height, image3_channels);
    auto gun_texture_matrix = gun_texture->get_transformation_matrix();
    int gun_sprite_frame_count = 6;
    float gun_sprite_size = 1.0f / (float) gun_sprite_frame_count;
    gun_texture_matrix[0][0] = gun_sprite_size;
    gun_texture->set_transformation_matrix(gun_texture_matrix);
    gun_texture->set_transformation_enabled(true);
    gun_texture->set_minification_filter(Texture::FilterType::Nearest);
    gun_texture->set_magnification_filter(Texture::FilterType::Nearest);
    gun_material->set_texture_1(gun_texture);
    gun_material->set_blending_enabled(true);
    gun_material->set_overlay(true);
    auto gun = std::make_shared<Mesh>(gun_geometry, gun_material);
    gun->set_scale(glm::vec3(4.0f));
    gun->add_to_y(-1.0f);
    GunState gun_state = Idling;

    // Lights

    auto[lamp_indices, lamp_vertices] = geometry_generators::generate_sphere_geometry_data(0.025f, 10, 10);
    auto lamp_geometry = std::make_shared<ES2Geometry>(lamp_indices, lamp_vertices);
    auto lamp_material = std::make_shared<ES2ConstantMaterial>();
    auto lamp = std::make_shared<Mesh>(lamp_geometry, lamp_material);

    glm::vec3 point_light_ambient_color(0.0f);
    glm::vec3 point_light_diffuse_color(1.0f);
    glm::vec3 point_light_specular_color(1.0f);

    auto point_light = std::make_shared<PointLight>();
    point_light->set_intensity(1.2f);
    point_light->set_two_sided(true);
    lamp->add_child(point_light);

    // Camera

    auto camera = std::make_shared<Camera>();
    camera->set_z(2.0f);
    camera->set_y(0.1f);

    // Scene

    std::vector<std::shared_ptr<Object>> objects{floor, lamp, demon, gun};
    auto scene = std::make_shared<Scene>(objects);
    scene->get_point_lights().push_back(point_light);
    scene->set_camera(camera);

    // Events

    auto previous_key_input_time = std::chrono::high_resolution_clock::now();
    window->set_on_late_keys_down([&](const uint8_t *keys) {
        float delta_time = find_delta_time(previous_key_input_time);

        static const glm::vec4 forward = glm::vec4(0.0f, 0.0f, 1.0f, 0.0f);
        static const glm::vec4 right = glm::vec4(1.0f, 0.0f, 0.0f, 0.0f);
        static const float camera_speed = 0.1f;

        if (keys[SDL_SCANCODE_W]) {
            camera->add_to_position(-camera->get_model_matrix() * forward * camera_speed * delta_time);
        }
        if (keys[SDL_SCANCODE_A]) {
            camera->add_to_position(-camera->get_model_matrix() * right * camera_speed * delta_time);
        }
        if (keys[SDL_SCANCODE_S]) {
            camera->add_to_position(camera->get_model_matrix() * forward * camera_speed * delta_time);
        }
        if (keys[SDL_SCANCODE_D]) {
            camera->add_to_position(camera->get_model_matrix() * right * camera_speed * delta_time);
        }
        if (keys[SDL_SCANCODE_E]) {
            camera->add_to_y(camera_speed * delta_time);
        }
        if (keys[SDL_SCANCODE_Q]) {
            camera->add_to_y(-camera_speed * delta_time);
        }
        if (keys[SDL_SCANCODE_UP]) {
            camera->add_to_rotation_x(-camera_speed * delta_time);
        }
        if (keys[SDL_SCANCODE_DOWN]) {
            camera->add_to_rotation_x(camera_speed * delta_time);
        }
    });

    auto previous_mouse_input_time = std::chrono::high_resolution_clock::now();

    window->set_capture_mouse_enabled(true);
    window->set_relative_mouse_mode_enabled(true);
    window->set_on_mouse_move([&](int x, int y, int x_relative, int y_relative) {
        float delta_time = find_delta_time(previous_key_input_time);

        static const float camera_speed = 0.01f;
        camera->add_to_rotation_y((float) -x_relative * camera_speed * delta_time);
        camera->add_to_rotation_x((float) -y_relative * camera_speed * delta_time);

        /*
         * Code to debug ray/sphere intersection testing for shooting...
         *
            int cx = (int) ((float) window->get_width() / 2.0f);
            int cy = (int) ((float) window->get_height() / 2.0f);
            Ray ray = camera->world_ray_from_screen_point(cx, cy);

            auto [intersects, distance] = ray.intersects_with_sphere(demon_collision_sphere);
            if (intersects) {
                demon_material->set_emission_color(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
            } else {
                demon_material->set_emission_color(glm::vec4(1.0f));
            }
        */
    });

    Mix_Chunk *shotgun_sound = Mix_LoadWAV("data/audio/shotgun.wav");

    window->set_on_mouse_down([&](int button, int x, int y) {
        gun_state = Shooting;
        Mix_PlayChannel(-1, shotgun_sound, 0);

        int cx = (int) ((float) window->get_width() / 2.0f);
        int cy = (int) ((float) window->get_height() / 2.0f);
        Ray ray = camera->world_ray_from_screen_point(cx, cy);

        auto [intersects, distance] = ray.intersects_with_sphere(demon_collision_sphere);
        if (intersects && demon_state == Alive) {
            demon_state = Dying;
            demon_texture_matrix[3][0] = (float) demon_sprite_dying_first_frame * demon_sprite_size;
        }
    });

    // Game/Render Loop

    float demon_animation_timer = 0.0f;
    static const float demon_animation_delay = 1.0f;

    float gun_animation_timer = 0.0f;
    static const float gun_animation_delay = 1.0f;

    const float lamp_trajectory_radius = 1.0f;
    const float lamp_delta_angle = 0.09f;
    float lamp_angle = 0.0f;

    ES2Renderer renderer(scene, window);

    auto previous_frame_time = std::chrono::high_resolution_clock::now();
    for (;;) {
        float delta_time = find_delta_time(previous_frame_time);

        window->poll(); // consume and process events from the keyboard/mouse

        // Per-frame game logic goes here...

        lamp_angle += lamp_delta_angle * delta_time;
        float lamp_x = std::cosf(lamp_angle) * lamp_trajectory_radius;
        float lamp_z = std::sinf(lamp_angle) * lamp_trajectory_radius;
        lamp->set_x(lamp_x);
        lamp->set_z(lamp_z);

        if (demon_state == Alive || demon_state == Dying) {
            demon_animation_timer += delta_time;
            if (demon_animation_timer > demon_animation_delay) {
                demon_animation_timer = 0.0f;

                demon_texture_matrix = demon_texture->get_transformation_matrix();
                demon_texture_matrix[3][0] += demon_sprite_size;
                if (demon_state == Alive) {
                    if (demon_texture_matrix[3][0] > demon_sprite_size * (float) (demon_sprite_dying_first_frame - 1)) {
                        demon_texture_matrix[3][0] = 0.0f;
                    }
                } else if (demon_state == Dying) {
                    if (demon_texture_matrix[3][0] > demon_sprite_size * (float) (demon_sprite_frame_count - 1)) {
                        demon_state = Dead;
                    }
                }
                demon_texture->set_transformation_matrix(demon_texture_matrix);
            }
        }
        demon->billboard_toward_camera(camera);

        if (gun_state == Shooting) {
            gun_animation_timer += delta_time;
            if (gun_animation_timer > gun_animation_delay) {
                gun_animation_timer = 0.0f;

                gun_texture_matrix = gun_texture->get_transformation_matrix();
                gun_texture_matrix[3][0] += gun_sprite_size;
                if (gun_texture_matrix[3][0] > gun_sprite_size * (float) (gun_sprite_frame_count - 1)) {
                    gun_texture_matrix[3][0] = 0.0f;
                    gun_state = Idling;
                }
                gun_texture->set_transformation_matrix(gun_texture_matrix);
            }
        }

        // Command the GPU to display the updated game objects

        renderer.render();
    }

    Mix_FreeChunk(shotgun_sound);
}
