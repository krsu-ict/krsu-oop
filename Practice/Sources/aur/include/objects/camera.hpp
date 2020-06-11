#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "objects/object.hpp"
#include "math/ray.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace aur
{
    class Camera : public Object
    {
    public:
        Camera() : Object{"camera"} {
            _update_camera_sides();
        }

        bool is_perspective() const
        {
            return _perspective;
        }

        void set_perspective(bool perspective)
        {
            if (_perspective != perspective) {
                _perspective = perspective;
                if (!_perspective) {
                    _update_camera_sides();
                }
                set_projection_matrix_requires_update(true);
            }
        }

        bool should_receive_aspect_ratio_from_renderer() const
        {
            return _receive_aspect_ratio_from_renderer;
        }

        void set_receive_aspect_ratio_from_renderer(bool receive_aspect_ratio_from_renderer)
        {
            _receive_aspect_ratio_from_renderer = receive_aspect_ratio_from_renderer;
        }

        float get_aspect_ratio() const
        {
            return _aspect_ratio;
        }

        void set_aspect_ratio(float aspect_ratio)
        {
            if (_aspect_ratio != aspect_ratio) {
                _aspect_ratio = aspect_ratio;
                if (!_perspective) {
                    _update_camera_sides();
                }
                set_projection_matrix_requires_update(true);
            }
        }

        float get_field_of_view() const
        {
            return _field_of_view;
        }

        void set_field_of_view(float field_of_view)
        {
            if (_field_of_view != field_of_view) {
                _field_of_view = field_of_view;
                set_projection_matrix_requires_update(true);
            }
        }

        float get_near_plane() const
        {
            return _near_plane;
        }

        void set_near_plane(float near_plane)
        {
            if (_near_plane != near_plane) {
                _near_plane = near_plane;
                set_projection_matrix_requires_update(true);
            }
        }

        float get_far_plane() const
        {
            return _far_plane;
        }

        void set_far_plane(float far_plane)
        {
            if (_far_plane != far_plane) {
                _far_plane = far_plane;
                set_projection_matrix_requires_update(true);
            }
        }

        const glm::vec4 &get_viewport() const
        {
            return _viewport;
        }

        void set_viewport(const glm::vec4 &viewport)
        {
            _viewport = viewport;
        }

        bool should_receive_viewport_from_renderer() const
        {
            return _receive_viewport_from_renderer;
        }

        void set_receive_viewport_from_renderer(bool receive_viewport_from_renderer)
        {
            _receive_viewport_from_renderer = receive_viewport_from_renderer;
        }

        float get_zoom() const
        {
            return _zoom;
        }

        void set_zoom(float zoom)
        {
            if (_zoom != zoom) {
                _zoom = zoom;
                if (!_perspective) {
                    _update_camera_sides();
                }
                set_projection_matrix_requires_update(true);
            }
        }

        float get_left() const
        {
            return _left;
        }

        float get_right() const
        {
            return _right;
        }

        float get_bottom() const
        {
            return _bottom;
        }

        float get_top() const
        {
            return _top;
        }

        const glm::mat4 &get_view_matrix()
        {
            _update_view_matrix_if_necessary();

            return _view_matrix;
        }

        const glm::mat4 &get_projection_matrix()
        {
            _update_projection_matrix_if_necessary();

            return _projection_matrix;
        }

        glm::mat4 get_orthographic_projection_matrix()
        {
            if (_perspective) {
                _update_camera_sides();

                return glm::ortho<float>(
                    _left,
                    _right,
                    _bottom,
                    _top
                );
            } else {
                return get_projection_matrix();
            }
        }

        const glm::mat4 &get_view_projection_matrix()
        {
            _update_view_projection_matrix_if_necessary();

            return _view_projection_matrix;
        }

        void set_model_matrix_requires_update(bool model_matrix_requires_update) final
        {
            Object::set_model_matrix_requires_update(model_matrix_requires_update);

            if (model_matrix_requires_update) {
                _view_matrix_requires_update = true;
                _view_projection_matrix_requires_update = true;
            }
        }

        void set_world_matrix_requires_update(bool world_matrix_requires_update) final
        {
            Object::set_world_matrix_requires_update(world_matrix_requires_update);

            if (world_matrix_requires_update) {
                _view_matrix_requires_update = true;
                _view_projection_matrix_requires_update = true;
            }
        }

        bool is_view_matrix_requires_update() const
        {
            return _view_matrix_requires_update;
        }

        void set_view_matrix_requires_update(bool view_matrix_requires_update)
        {
            _view_matrix_requires_update = view_matrix_requires_update;
            if (_view_matrix_requires_update) {
                _view_projection_matrix_requires_update = true;
            }
        }

        bool is_projection_matrix_requires_update() const
        {
            return _projection_matrix_requires_update;
        }

        void set_projection_matrix_requires_update(bool projection_matrix_requires_update)
        {
            _projection_matrix_requires_update = projection_matrix_requires_update;
            if (_projection_matrix_requires_update) {
                _view_projection_matrix_requires_update = true;
            }
        }

        bool is_view_projection_matrix_requires_update() const
        {
            return _view_projection_matrix_requires_update;
        }

        void set_view_projection_matrix_requires_update(bool view_projection_matrix_requires_update)
        {
            _view_projection_matrix_requires_update = view_projection_matrix_requires_update;
        }

        Ray world_ray_from_screen_point(int x, int y) {
            return world_ray_from_screen_point(x, y, _viewport);
        }

        Ray world_ray_from_screen_point(int x, int y, glm::vec4 viewport) {
            glm::vec2 screen_point = glm::vec2(x, static_cast<int>(viewport[3]) - y);

            glm::vec3 near = glm::vec3(screen_point, 0.0f);
            near = glm::unProject(near, get_view_matrix(), get_projection_matrix(), viewport);

            glm::vec3 far = glm::vec3(screen_point, 1.0f);
            far = glm::unProject(far, get_view_matrix(), get_projection_matrix(), viewport);

            Ray world_ray{near, glm::normalize(far - near)};

            return world_ray;
        }

    private:
        bool _perspective{true};

        bool _receive_aspect_ratio_from_renderer{true};
        float _aspect_ratio{1.0f};
        float _field_of_view{1.13f};
        float _near_plane{0.01f};
        float _far_plane{1000.0f};

        glm::vec4 _viewport{0, 0, 1920, 1080};
        bool _receive_viewport_from_renderer{true};

        float _zoom{3.0f};
        float _left{INFINITY};
        float _right{INFINITY};
        float _bottom{INFINITY};
        float _top{INFINITY};

        bool _view_matrix_requires_update{true};
        glm::mat4 _view_matrix{1.0f};
        bool _projection_matrix_requires_update{true};
        glm::mat4 _projection_matrix{1.0f};
        bool _view_projection_matrix_requires_update{true};
        glm::mat4 _view_projection_matrix{1.0f};

        void _update_view_matrix_if_necessary()
        {
            if (_view_matrix_requires_update) {
                _update_world_matrix_if_necessary();

                _view_matrix = glm::inverse(_world_matrix);
                _view_matrix_requires_update = false;
            }
        }

        void _update_projection_matrix_if_necessary()
        {
            if (_projection_matrix_requires_update) {
                if (_perspective) {
                    _projection_matrix = glm::perspective<float>(
                        _field_of_view,
                        _aspect_ratio,
                        _near_plane,
                        _far_plane
                    );
                } else {
                    _projection_matrix = glm::ortho<float>(
                        _left,
                        _right,
                        _bottom,
                        _top
                    );
                }
                _projection_matrix_requires_update = false;
            }
        }

        void _update_view_projection_matrix_if_necessary()
        {
            if (_view_projection_matrix_requires_update) {
                _update_view_matrix_if_necessary();
                _update_projection_matrix_if_necessary();

                _view_projection_matrix = _projection_matrix * _view_matrix;
                _view_projection_matrix_requires_update = false;
            }
        }

        void _update_camera_sides()
        {
            _left = -(_zoom * _aspect_ratio);
            _right = _zoom * _aspect_ratio;
            _bottom = -_zoom;
            _top = _zoom;
        }
    };
}

#endif
