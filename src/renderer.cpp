#include "renderer.hpp"
#include <GLFW/glfw3.h>
#include <iostream>
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

namespace transport
{

    void framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        auto& rend = Renderer::GetInstance();
        rend.width_ = width;
        rend.height_ = height;
        glViewport(0, 0, width, height);
        rend.UpdateProjection();
    }

    void Renderer::UpdateProjection()
    {
        projection_ = glm::ortho(-width_/2., width_/2., -height_/2., height_/2.);
    }

    bool Renderer::Initialize()
    {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        window_ = glfwCreateWindow(width_, height_, "Transport", NULL, NULL);
        if (window_ == NULL)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return false;
        }
        glfwMakeContextCurrent(window_);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return -1;
        }

        glViewport(0, 0, width_, height_);
        glfwSetFramebufferSizeCallback(window_, framebuffer_size_callback);

        glClearColor(1.f, 1.f, 1.f, 1.0f);
        return true;
    }

    void Renderer::Terminate()
    {
        glfwTerminate();
    }

    bool Renderer::ShouldClose()
    {
        return glfwWindowShouldClose(window_);
    }

    void Renderer::Render()
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window_);
        glfwPollEvents();
    }
}
