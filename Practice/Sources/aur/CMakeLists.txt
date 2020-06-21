cmake_minimum_required(VERSION 3.10.2)
project(aur)

set(CMAKE_CXX_STANDARD 17)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

if(MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

include_directories("./include")

set(AUR_SOURCES
        include/vendor/imgui_impl_opengl.h
        include/vendor/imgui_impl_sdl.h
        include/math/plane.hpp
        include/math/aabb.hpp
        include/math/sphere.hpp
        include/math/ray.hpp
        include/utilities/utilities.hpp
        include/geometries/vertex.hpp
        include/geometries/geometry.hpp
        include/geometries/es2_geometry.hpp
        include/geometries/geometry_generators.hpp
        include/textures/texture.hpp
        include/textures/es2_texture.hpp
        include/materials/material.hpp
        include/materials/constant_material.hpp
        include/materials/es2_constant_material.hpp
        include/materials/phong_material.hpp
        include/materials/es2_phong_material.hpp
        include/objects/object.hpp
        include/objects/mesh.hpp
        include/objects/camera.hpp
        include/lights/light.hpp
        include/lights/ambient_light.hpp
        include/lights/directional_light.hpp
        include/lights/point_light.hpp
        include/lights/spot_light.hpp
        include/scene/scene.hpp
        include/window/window.hpp
        include/window/sdl_window.hpp
        include/renderer/shader.hpp
        include/renderer/es2_shader.hpp
        include/renderer/renderer.hpp
        include/renderer/es2_renderer.hpp
        include/aur.hpp
)

add_executable(window_test ${AUR_SOURCES} tests/window_test.cpp)
add_executable(triangle_test ${AUR_SOURCES} tests/triangle_test.cpp)
add_executable(other_geometries_test ${AUR_SOURCES} tests/other_geometries_test.cpp)
add_executable(scene_graph_test ${AUR_SOURCES} tests/scene_graph_test.cpp)
add_executable(lighting_test ${AUR_SOURCES} tests/lighting_test.cpp)
add_executable(material_properties_test ${AUR_SOURCES} tests/material_properties_test.cpp)
add_executable(textured_plane_test ${AUR_SOURCES} tests/textured_plane_test.cpp)
add_executable(normal_mapping_test ${AUR_SOURCES} tests/normal_mapping_test.cpp)
add_executable(geometry_streaming_test ${AUR_SOURCES} tests/geometry_streaming_test.cpp)
add_executable(general_usage_test ${AUR_SOURCES} tests/general_usage_test.cpp)

target_link_libraries(window_test ${CONAN_LIBS})
target_link_libraries(triangle_test ${CONAN_LIBS})
target_link_libraries(other_geometries_test ${CONAN_LIBS})
target_link_libraries(scene_graph_test ${CONAN_LIBS})
target_link_libraries(lighting_test ${CONAN_LIBS})
target_link_libraries(material_properties_test ${CONAN_LIBS})
target_link_libraries(textured_plane_test ${CONAN_LIBS})
target_link_libraries(normal_mapping_test ${CONAN_LIBS})
target_link_libraries(geometry_streaming_test ${CONAN_LIBS})
target_link_libraries(general_usage_test ${CONAN_LIBS})

add_executable(game ${AUR_SOURCES} game/main.cpp)
target_link_libraries(game ${CONAN_LIBS})
