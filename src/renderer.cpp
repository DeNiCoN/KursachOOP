#include "renderer.hpp"
#include <GLFW/glfw3.h>
#include <iostream>
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

namespace transport
{
    void GLAPIENTRY
    MessageCallback( GLenum source,
                     GLenum type,
                     GLuint id,
                     GLenum severity,
                     GLsizei length,
                     const GLchar* message,
                     const void* userParam )
    {
        fprintf( stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
                 ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
                 type, severity, message );
    }


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

    void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
    {
        auto& renderer = Renderer::GetInstance();
        auto& smooth_zoom = renderer.smooth_zoom_;
        double xpos, ypos;
        glfwGetCursorPos(renderer.window_, &xpos, &ypos);
        glm::vec2 cPos = glm::vec2((float) xpos - renderer.width_ / 2.f,
                                   (float) -ypos + renderer.height_ / 2.f);
        smooth_zoom.addScale(yoffset * smooth_zoom.getFinalScale() * 0.09f,
                               9, cPos);
    }

    void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
    {
        static double p_xpos = 0;
        static double p_ypos = 0;
        double dx = p_xpos - xpos;
        double dy = p_ypos - ypos;
        p_xpos = xpos;
        p_ypos = ypos;
        int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);

        auto& renderer = Renderer::GetInstance();
        if (state == GLFW_PRESS)
        {
            //update cam position and dont forget about scale
            renderer.cam_position_ += glm::vec2(-dx, dy) * (float) (1.f / renderer.cam_scale_);
        }
    }

    void Renderer::UpdateProjection()
    {
        projection_ = glm::ortho(-(width_/2.f), width_/2.f, -(height_/2.f), height_/2.f);
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

uniform mat4 projection_view;

uniform mat4 model;

void main()
{
    //Model to world, then move camera and project
	gl_Position = projection_view * model * vec4(aPos, 1.0);
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
    vec4 tex_color = texture(texture1, TexCoord) * color;
    if(tex_color.a < 0.1)
        discard;
    FragColor = tex_color;
})";


    unsigned int line_shader_;
    unsigned int line_VBO, line_VAO;
    const char* line_vs = R"(
#version 330 core
layout (location = 0) in vec2 aPos;

uniform mat4 projection_view;

void main()
{
    gl_Position = projection_view * vec4(aPos, 0.0f, 1.0);
}

)";
    const char* line_fs = R"(
#version 330 core
out vec4 FragColor;

void main()
{
    FragColor = vec4(0.1f, 0.1f, 0.13f, 1.f);
}
)";

    bool Renderer::Initialize()
    {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_SAMPLES, 8);

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
        glfwSetScrollCallback(window_, scroll_callback);
        glfwSetCursorPosCallback(window_, cursor_position_callback);

        //glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(MessageCallback, 0);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_MULTISAMPLE);
        glEnable(GL_SAMPLE_SHADING);
        glMinSampleShading(1.f);
        glEnable(GL_LINE_SMOOTH);
        glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

        glClearColor(1.f, 1.f, 1.f, 1.0f);
        UpdateProjection();

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

        line_shader_ = CompileShader(line_vs, line_fs);
        glGenVertexArrays(1, &line_VAO);
        glGenBuffers(1, &line_VBO);
        glBindVertexArray(line_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, line_VBO);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

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
    void Renderer::DrawTexture(TextureHandle texture, glm::vec3 position,
                               glm::vec2 scale, float angle, glm::vec4 color)
    {
        auto model = glm::translate(glm::mat4(1.f), position);
        model = glm::scale(model, glm::vec3(scale, 1.));
        model = glm::rotate(model, angle, glm::vec3{0.f, 0.f, 1.f});
        sprite_batch_.push_back({model, color, texture});
    }

    void Renderer::Update(double delta)
    {
        sprite_batch_.clear();
        line_batch_.clear();

        if (smooth_zoom_.GetState() == Process::State::RUNNING)
        {
            smooth_zoom_.Update(delta);
        }
    }
    void Renderer::Render()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        projection_view_ = glm::scale(projection_, glm::vec3(cam_scale_, cam_scale_, 1));
        projection_view_ = glm::translate(projection_view_, glm::vec3(cam_position_, 0));
        RenderLines();
        RenderSprites();

        glfwSwapBuffers(window_);
        glfwPollEvents();
    }

    //Naive rendering, no sorting, instancing, no anything
    void Renderer::RenderSprites()
    {
        glUseProgram(sprite_shader_);
        glUniformMatrix4fv(glGetUniformLocation(sprite_shader_, "projection_view"),
                           1, GL_FALSE, &projection_view_[0][0]);
        glBindVertexArray(sprite_VAO);
        for (const auto& sprite : sprite_batch_)
        {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, sprite.texture);
            glUniform4fv(glGetUniformLocation(sprite_shader_, "color"),
                         1, &sprite.color[0]);
            glUniformMatrix4fv(glGetUniformLocation(sprite_shader_, "model"),
                               1, GL_FALSE, &sprite.model[0][0]);

            glDrawArrays(GL_TRIANGLES, 0, 6);
        }
    }

    void Renderer::RenderLines()
    {
        glUseProgram(line_shader_);
        glUniformMatrix4fv(glGetUniformLocation(line_shader_, "projection_view"),
                           1, GL_FALSE, &projection_view_[0][0]);

        glLineWidth(10.f*cam_scale_);

        glBindVertexArray(line_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, line_VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 4 * line_batch_.size(),
                     (float*)line_batch_.data(), GL_DYNAMIC_DRAW);
        glDrawArrays(GL_LINES, 0, 2*line_batch_.size());
    }
}
