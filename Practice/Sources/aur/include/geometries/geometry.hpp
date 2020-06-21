#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#include "materials/material.hpp"
#include "geometries/vertex.hpp"

#include <vector>
#include <utility>

#include <glm/glm.hpp>

namespace aur
{
    class Geometry
    {
    public:
        enum Type
        {
            Points,
            Lines,
            LineLoop,
            LineStrip,
            Triangles,
            TriangleFan,
            TriangleStrip
        };

        enum UsageStrategy
        {
            StaticStrategy,
            DynamicStrategy,
            StreamStrategy
        };

        explicit Geometry(std::vector<unsigned int> indices, std::vector<Vertex> vertices)
            : _indices(std::move(indices)), _vertices(std::move(vertices))
        {}

        virtual ~Geometry() = default;

        [[nodiscard]] Type get_type() const
        {
            return _type;
        }

        void set_type(Type type)
        {
            _type = type;
        }

        [[nodiscard]] const std::vector<unsigned int> &get_indices() const
        {
            return _indices;
        }

        [[nodiscard]] std::vector<unsigned int> &get_indices()
        {
            return _indices;
        }

        void set_indices(const std::vector<unsigned int> &indices)
        {
            _indices = indices;
            _requires_indices_update = true;
        }

        [[nodiscard]] const std::vector<Vertex> &get_vertices() const
        {
            return _vertices;
        }

        [[nodiscard]] std::vector<Vertex> &get_vertices()
        {
            return _vertices;
        }

        void set_vertices(const std::vector<Vertex> &vertices)
        {
            _vertices = vertices;
            _requires_vertices_update = true;
        }

        void set_requires_indices_update(bool requires_indices_update)
        {
            _requires_indices_update = requires_indices_update;
        }

        void set_requires_vertices_update(bool requires_vertices_update)
        {
            _requires_vertices_update = requires_vertices_update;
        }

        [[nodiscard]] UsageStrategy get_vertices_usage_strategy() const
        {
            return _vertices_usage_strategy;
        }

        void set_vertices_usage_strategy(UsageStrategy vertices_usage_strategy)
        {
            if (_vertices_usage_strategy != vertices_usage_strategy) {
                _vertices_usage_strategy = vertices_usage_strategy;
                _requires_vertices_update = true;
            }
        }

        [[nodiscard]] UsageStrategy get_indices_usage_strategy() const
        {
            return _indices_usage_strategy;
        }

        void set_indices_usage_strategy(UsageStrategy indices_usage_strategy)
        {
            if (_indices_usage_strategy != indices_usage_strategy) {
                _indices_usage_strategy = indices_usage_strategy;
                _requires_indices_update = true;
            }
        }

        [[nodiscard]] float get_line_width() const
        {
            return _line_width;
        }

        void set_line_width(float lineWidth)
        {
            _line_width = lineWidth;
        }

        void transform(glm::mat4 transformation_matrix)
        {
            for (auto &vertex : _vertices) {
                vertex.position = glm::vec3(transformation_matrix * glm::vec4(vertex.position, 1.0f));
            }
            _requires_vertices_update = true;
        }

        void calculate_tangents_and_binormals()
        {
            if (_type != Triangles && _type != TriangleStrip && _type != TriangleFan) {
                return;
            }

            for (auto &vertex : _vertices) {
                vertex.tangent = glm::vec4(0.0f);
                vertex.binormal = glm::vec3(0.0f);
            }

            std::vector<unsigned int>::size_type index = _type == TriangleFan ? 1 : 0;
            while (index < _indices.size()) {
                std::vector<unsigned int>::size_type a_index, b_index, c_index;
                switch (_type) {
                    case Triangles:
                        a_index = index;
                        b_index = index + 1;
                        c_index = index + 2;
                        index += 3;
                        break;
                    case TriangleStrip:
                        a_index = index;
                        b_index = index + 1;
                        c_index = index + 2;
                        ++index;
                        break;
                    case TriangleFan:
                        a_index = 0;
                        b_index = index;
                        c_index = index + 1;
                        ++index;
                        break;
                    default:
                        return;
                }

                Vertex &a = _vertices[_indices[a_index]];
                Vertex &b = _vertices[_indices[b_index]];
                Vertex &c = _vertices[_indices[c_index]];

                glm::vec4 a_texture_coordinates = a.texture1_coordinates;
                glm::vec4 b_texture_coordinates = b.texture1_coordinates;
                glm::vec4 c_texture_coordinates = c.texture1_coordinates;

                glm::vec3 q1 = b.position - a.position;
                glm::vec3 q2 = c.position - a.position;

                float s1 = b_texture_coordinates.s - a_texture_coordinates.s;
                float s2 = c_texture_coordinates.s - a_texture_coordinates.s;
                float t1 = b_texture_coordinates.t - a_texture_coordinates.t;
                float t2 = c_texture_coordinates.t - a_texture_coordinates.t;

                glm::vec3 tangent = glm::normalize((q1 * t2) - (q2 * t1));
                glm::vec3 binormal = glm::normalize((q2 * s1) - (q1 * s2));

                a.tangent += glm::vec4(tangent, 0.0f);
                b.tangent += glm::vec4(tangent, 0.0f);
                c.tangent += glm::vec4(tangent, 0.0f);

                a.binormal += binormal;
                b.binormal += binormal;
                c.binormal += binormal;
            }

            for (auto &vertex : _vertices) {
                glm::vec3 normal = vertex.normal;
                glm::vec3 tangent = vertex.tangent;
                glm::vec3 binormal = vertex.binormal;

                tangent = glm::normalize(tangent - (normal * glm::dot(tangent, normal)));
                glm::vec4 tangent_with_determinant = glm::vec4(tangent, 0.0f);

                bool mirrored = glm::dot(glm::cross(normal, tangent), binormal) < 0.0f;
                tangent_with_determinant[3] = mirrored ? 1.0f : -1.0f;

                vertex.tangent = tangent_with_determinant;
                vertex.binormal = glm::cross(normal, tangent) * tangent_with_determinant[3];
            }

            _requires_vertices_update = true;
        }

        virtual void update(const Material &material) = 0;

        virtual void use() = 0;

    protected:
        Type _type{Triangles};

        std::vector<unsigned int> _indices;
        bool _requires_indices_update{true};
        std::vector<Vertex> _vertices;
        bool _requires_vertices_update{true};

        UsageStrategy _vertices_usage_strategy{StaticStrategy};
        UsageStrategy _indices_usage_strategy{StaticStrategy};

        float _line_width{1.0f};
    };
}

#endif
