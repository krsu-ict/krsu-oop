#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <utility>

#include "scene/scene.hpp"
#include "window/window.hpp"

namespace aur
{
    class Renderer
    {
    public:
        Renderer(std::shared_ptr<Scene> scene, std::shared_ptr<Window> window)
            : _scene(std::move(scene)), _window(std::move(window))
        {}

        virtual ~Renderer() = default;

        virtual void render() = 0;

    protected:
        std::shared_ptr<Scene> _scene;
        std::shared_ptr<Window> _window;
    };
}

#endif
