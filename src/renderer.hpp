#pragma once
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace transport
{
    /*
    ** Рендерер отвечает за создание окна и рисование на нём
    */
    class Renderer
    {
    public:
        static Renderer& GetInstance()
        {
            static Renderer instance;
            return instance;
        }
        using Texture = int;
        void DrawTexture(Texture texture, glm::vec2 position,
                         float scale, float angle, glm::vec4 color) {}
        void DrawLine(glm::vec2 from, glm::vec2 to,
                      float thickness, glm::vec3 color) {}
        void Render();

        bool ShouldClose();

        bool Initialize();
        void Terminate();
    private:
        Renderer() {}
        void UpdateProjection();

        unsigned width_ = 800;
        unsigned height_ = 600;
        GLFWwindow* window_;

        glm::mat4 projection_;

        float cam_scale_ = 1.f;
        glm::vec2 cam_position_ = {0., 0.};

        friend void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    };
}
