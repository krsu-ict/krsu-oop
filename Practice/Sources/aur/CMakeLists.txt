cmake_minimum_required(VERSION 3.10.2)
project(aur)

set(CMAKE_CXX_STANDARD 17)
set(
    AUR_SOURCES
        include/aur.hpp
        include/geometries/es2_geometry.hpp
        include/geometries/geometry.hpp
        include/geometries/geometry_generators.hpp
        include/geometries/vertex.hpp
        include/lights/ambient_light.hpp
        include/lights/directional_light.hpp
        include/lights/light.hpp
        include/lights/point_light.hpp
        include/lights/spot_light.hpp
        include/materials/constant_material.hpp
        include/materials/es2_constant_material.hpp
        include/materials/es2_phong_material.hpp
        include/materials/material.hpp
        include/materials/phong_material.hpp
        include/math/aabb.hpp
        include/math/plane.hpp
        include/math/ray.hpp
        include/math/sphere.hpp
        include/objects/camera.hpp
        include/objects/mesh.hpp
        include/objects/object.hpp
        include/renderer/es2_renderer.hpp
        include/renderer/es2_shader.hpp
        include/renderer/renderer.hpp
        include/renderer/shader.hpp
        include/scene/scene.hpp
        include/textures/es2_texture.hpp
        include/textures/texture.hpp
        include/utilities/utilities.hpp
        include/window/sdl_window.hpp
        include/window/window.hpp
)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

include_directories("./include")
add_executable(game ${AUR_SOURCES} game/main.cpp)
target_link_libraries(game ${CONAN_LIBS})
