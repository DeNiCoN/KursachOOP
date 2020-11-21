#pragma once
#include "empty_renderer.hpp"

namespace transport
{
    class EmptyWindow
    {
    public:
        using Renderer = Renderer;
        Renderer& GetRenderer() { return renderer_; }
    private:
        Renderer renderer_;
    };
}
