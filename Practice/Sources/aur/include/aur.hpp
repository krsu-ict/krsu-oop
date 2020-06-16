#ifndef AUR_HPP
#define AUR_HPP

#include "objects/object.hpp"
#include "objects/mesh.hpp"
#include "objects/camera.hpp"
#include "lights/light.hpp"
#include "lights/ambient_light.hpp"
#include "lights/directional_light.hpp"
#include "lights/point_light.hpp"
#include "lights/spot_light.hpp"
#include "geometries/vertex.hpp"
#include "geometries/geometry.hpp"
#include "geometries/es2_geometry.hpp"
#include "geometries/geometry_generators.hpp"
#include "textures/texture.hpp"
#include "textures/es2_texture.hpp"
#include "materials/material.hpp"
#include "materials/constant_material.hpp"
#include "materials/es2_constant_material.hpp"
#include "materials/phong_material.hpp"
#include "materials/es2_phong_material.hpp"
#include "scene/scene.hpp"
#include "window/window.hpp"
#include "window/sdl_window.hpp"
#include "renderer/shader.hpp"
#include "renderer/es2_shader.hpp"
#include "renderer/renderer.hpp"
#include "renderer/es2_renderer.hpp"
#include "math/ray.hpp"
#include "math/plane.hpp"
#include "math/aabb.hpp"
#include "math/sphere.hpp"
#include "utilities/utilities.hpp"

#include <glm/glm.hpp>
#include "glm/gtx/string_cast.hpp"
#include <imgui.h>

#endif
