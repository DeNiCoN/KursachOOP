#pragma once
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glad/glad.h>
#include <vector>
#include <GLFW/glfw3.h>
#include "smooth_zoom_process.hpp"

namespace transport
{
    class Renderer
    {
    public:
        static Renderer& GetInstance()
        {
            static Renderer instance;
            return instance;
        }
        using TextureHandle = unsigned;

        void DrawTexture(TextureHandle texture, glm::vec3 position,
                         glm::vec2 scale, float angle, glm::vec4 color);

        void DrawLine(glm::vec2 from, glm::vec2 to,
                      float thickness, glm::vec3 color)
        {
            line_batch_.push_back({from, to, color, thickness});
        }

        void Render();
        void Update(double delta);

        bool ShouldClose();

        bool Initialize();
        void Terminate();
    private:
        Renderer() {}
        void UpdateProjection();

        struct Line
        {
            glm::vec2 from;
            glm::vec2 to;
            glm::vec3 color;
            float thickness;
        };

        struct Sprite
        {
            glm::mat4 model;
            glm::vec4 color;
            TextureHandle texture;
        };

        std::vector<Sprite> sprite_batch_;
        std::vector<Line> line_batch_;

        void RenderSprites();
        void RenderLines();

        unsigned width_ = 800;
        unsigned height_ = 600;
        GLFWwindow* window_;

        glm::mat4 projection_;
        glm::mat4 projection_view_;

        float cam_scale_ = 1.f;
        glm::vec2 cam_position_ = {0., 0.};

        SmoothZoom smooth_zoom_ {cam_scale_, cam_position_};

        friend void framebuffer_size_callback(GLFWwindow* window, int width, int height);
        friend void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
        friend void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    };
}
