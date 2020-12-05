#pragma once
#include "renderer.hpp"
#include <glm/vec4.hpp>


namespace transport
{
    class GraphicsObject
    {
    public:
        virtual const Renderer::TextureHandle GetTexture() const = 0;
        virtual glm::vec3 GetColor() const { return {1., 1., 1.}; };
        virtual ~GraphicsObject() = default;
    };
}
