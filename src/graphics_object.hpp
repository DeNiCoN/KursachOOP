#pragma once
#include "renderer.hpp"
#include <glm/vec4.hpp>


namespace transport
{
    class GraphicsObject
    {
    public:
        virtual const Renderer::TextureHandle GetTexture() const = 0;
        virtual glm::vec4 GetColor() { return {0., 0., 0., 0.}; };
        virtual ~GraphicsObject() = default;
    };
}
