#include "renderer.hpp"
#include <GLFW/glfw3.h>
#include <iostream>
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

namespace transport
{

    unsigned CompileShader(const char* vertex_code, const char* fragment_code) {
        unsigned int vertex, fragment;
        int success;
        char infoLog[512];

// vertex Shader
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vertex_code, NULL);
        glCompileShader(vertex);
// print compile errors if any
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(vertex, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        };

// similiar for Fragment Shader
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fragment_code, NULL);
        glCompileShader(fragment);
// print compile errors if any
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(fragment, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        };

// shader Program
        unsigned ID;
        ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        glLinkProgram(ID);
// print linking errors if any
        glGetProgramiv(ID, GL_LINK_STATUS, &success);
        if(!success)
        {
            glGetProgramInfoLog(ID, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }

// delete the shaders as they're linked into our program now and no longer necessary
        glDeleteShader(vertex);
        glDeleteShader(fragment);

        return ID;
    }

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

    unsigned int sprite_shader_;
    unsigned int sprite_VBO, sprite_VAO;
    const float sprite_vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f
    };

    const char* sprite_vs = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

uniform mat4 projection;
uniform vec2 cam_offset;
uniform float cam_scale;

uniform mat4 model;

void main()
{
    //Model to world, then move camera and project
	gl_Position = projection * ((model * vec4(aPos, 1.0) - vec4(cam_offset, 0., 0.)) * cam_scale);
	TexCoord = vec2(aTexCoord.x, aTexCoord.y);
})";

    const char* sprite_fs = R"(#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

// texture samplers
uniform sampler2D texture1;
uniform vec4 color;

void main()
{
	FragColor = texture(texture1, TexCoord) * color;
})";

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

        sprite_shader_ = CompileShader(sprite_vs, sprite_fs);
        glUniform1i(glGetUniformLocation(sprite_shader_, "texture1"), 0);


        glGenVertexArrays(1, &sprite_VAO);
        glGenBuffers(1, &sprite_VBO);

        glBindVertexArray(sprite_VAO);

        glBindBuffer(GL_ARRAY_BUFFER, sprite_VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(sprite_vertices), sprite_vertices, GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // texture coord attribute
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
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
    void Renderer::DrawTexture(Texture texture, glm::vec3 position,
                               glm::vec2 scale, float angle, glm::vec4 color)
    {
        auto model = glm::scale(glm::mat4(), glm::vec3(scale, 1.));
        model = glm::rotate(model, angle, glm::vec3{0.f, 0.f, 1.f});
        model = glm::translate(model, position);
        sprite_batch_.push_back({model, color, texture});
    }

    void Renderer::Render()
    {
        glClear(GL_COLOR_BUFFER_BIT);

        RenderLines();
        RenderSprites();

        glfwSwapBuffers(window_);
        glfwPollEvents();
    }

    //Naive rendering, no sorting, instancing, no anything
    void Renderer::RenderSprites()
    {
        glUseProgram(sprite_shader_);
        glUniformMatrix4fv(glGetUniformLocation(sprite_shader_, "projection"),
                           1, GL_FALSE, &projection_[0][0]);
        glUniform2fv(glGetUniformLocation(sprite_shader_, "cam_offset"),
                     1, &cam_position_[0]);
        glUniform1f(glGetUniformLocation(sprite_shader_, "cam_scale"), cam_scale_);
        for (const auto& sprite : sprite_batch_)
        {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, sprite.texture);
            glUniform4fv(glGetUniformLocation(sprite_shader_, "color"),
                         1, &sprite.color[0]);
            glUniformMatrix4fv(glGetUniformLocation(sprite_shader_, "model"),
                               1, GL_FALSE, &sprite.model[0][0]);

            glBindVertexArray(sprite_VAO);
            glDrawArrays(GL_TRIANGLES, 0, 6);
        }
    }

    void Renderer::RenderLines()
    {
        for (const auto& line : line_batch_)
        {

        }
    }
}
