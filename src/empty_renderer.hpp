#pragma once
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

namespace Transport
{
    /*
    ** Рендерер отвечает за создание окна и рисование на нём
    */
    class EmptyRenderer
    {
    public:
        using Texture = int;
        void drawTexture(Texture, glm::vec2 position, float scale, float angle) {}
        void drawLine(glm::vec2 from, glm::vec2 to, glm::vec3 color) {}
        void update() {}
    };
}
