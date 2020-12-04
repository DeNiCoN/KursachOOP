#pragma once
#include <string>
#include "renderer.hpp"
#include <unordered_map>

namespace transport
{
    class TextureLoader
    {
    public:
        static Renderer::TextureHandle Load(const std::string& path);

    private:
        static std::unordered_map<std::string, Renderer::TextureHandle> cache_;
    };
}
