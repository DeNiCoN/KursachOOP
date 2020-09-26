#pragma once
#include "glm/vec2.hpp"
#include "empty_renderer.hpp"

namespace Transport
{
    /*
    ** Отвечает за рисование вершин, дорог и машин их позицию
    */
    class Graphics
    {
    private:
        using Renderer = EmptyRenderer;
    public:
        struct Vertex
        {
            glm::vec2 position;
        };

        struct Road
        {
            Vertex from, to;
        };

    };
}
