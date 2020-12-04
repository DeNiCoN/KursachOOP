#pragma once
#include "renderer.hpp"


namespace transport
{
    class GraphicsObject
    {
    public:
        virtual const Renderer::Texture& GetTexture() const = 0;
        virtual ~GraphicsObject() = default;
    };
}
