#pragma once
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

namespace transport
{
    /*
    ** Рендерер отвечает за создание окна и рисование на нём
    */
    class Renderer
    {
    public:
        using Texture = int;
        void DrawTexture(Texture, glm::vec2 position, float scale, float angle) {}
        void DrawLine(glm::vec2 from, glm::vec2 to, glm::vec3 color) {}
        void Render() {}
    };
}
