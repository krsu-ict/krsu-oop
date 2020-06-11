#ifndef VERTEX_HPP
#define VERTEX_HPP

namespace aur
{
    struct Vertex
    {
        glm::vec3 position{0.0f};
        glm::vec4 color{1.0f};
        glm::vec3 normal{0.0f};
        glm::vec4 tangent{0.0f};
        glm::vec3 binormal{0.0f};
        glm::vec4 texture1_coordinates{0.0f};
        glm::vec4 texture2_coordinates{0.0f};
    };
}

#endif
